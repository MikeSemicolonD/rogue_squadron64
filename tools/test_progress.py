import unittest, tempfile, pathlib, subprocess, sys
HERE = pathlib.Path(__file__).parent

YAML = """
name: Test
segments:
  - name: main
    type: code
    start: 0x1000
    subsegments:
      - [0x1000, c, "main/a"]
      - [0x1060, asm, "main/b"]
      - [0x1080, data, "main/c"]
      - {type: bss, vram: 0x80200000, name: "main/d"}
  - name: ovl
    type: code
    start: 0x1100
    subsegments:
      - [0x1100, c, "ovl/e"]
      - [0x1140, .data, "ovl/e"]
  - [0x1200]
"""

def insn(n, base=0x1000):
    return "".join(f"    /* {base + 4 * i:X} {0x80000400 + 4 * i:08X} 00000000 */  nop\n" for i in range(n))

class T(unittest.TestCase):
    def setUp(self):
        self.d = pathlib.Path(tempfile.mkdtemp())
        (self.d / "roguesquadron.yaml").write_text(YAML)
        (self.d / "src/main").mkdir(parents=True)
        (self.d / "src/ovl").mkdir(parents=True)
        (self.d / "src/main/a.c").write_text('INCLUDE_ASM("asm/nonmatchings/main/a", funcA);\nvoid funcZ(void) {}\n')
        (self.d / "src/ovl/e.c").write_text("void funcE(void) {}\n")
        nm = self.d / "asm/nonmatchings/main/a"
        nm.mkdir(parents=True)
        (nm / "funcA.s").write_text("glabel funcA\n" + insn(8))
        (self.d / "asm/main").mkdir(parents=True)
        (self.d / "asm/main/b.s").write_text("glabel funcB\n" + insn(8))

    def run_progress(self, *args):
        return subprocess.run([sys.executable, str(HERE / "progress.py"), "--root", str(self.d), *args], capture_output=True, text=True)

    def test_per_group(self):
        r = self.run_progress()
        self.assertEqual(r.returncode, 0, r.stderr)
        self.assertIn("main: 64/128 bytes (50.0%), 2 functions in asm", r.stdout)
        self.assertIn("ovl: 64/64 bytes (100.0%), 0 functions in asm", r.stdout)
        self.assertIn("total: 128/192 bytes (66.7%), 2 functions in asm", r.stdout)

    def test_csv(self):
        r = self.run_progress("--csv")
        self.assertIn("group,decompiled_bytes,total_bytes,percent,asm_functions", r.stdout)
        self.assertIn("main,64,128,50.0,2", r.stdout)

    def test_missing_asm_file_fails(self):
        (self.d / "asm/nonmatchings/main/a/funcA.s").unlink()
        r = self.run_progress()
        self.assertNotEqual(r.returncode, 0)
        self.assertIn("funcA", r.stderr)

    def test_rodata_jtbl_not_counted(self):
        jt = ".section .rodata\n" + "".join(f"    /* {0x2000 + 4 * i:X} {0x80001000 + 4 * i:08X} 80000400 */ .word .L80000400\n" for i in range(4))
        p = self.d / "asm/nonmatchings/main/a/funcA.s"
        p.write_text(jt + ".section .text\nglabel funcA\n" + insn(8))
        r = self.run_progress()
        self.assertIn("main: 64/128 bytes (50.0%)", r.stdout)

    def test_duplicate_include_counted_once(self):
        (self.d / "src/main/a.c").write_text('#ifdef NON_MATCHING\nvoid funcA(void) {}\n#else\nINCLUDE_ASM("asm/nonmatchings/main/a", funcA);\n#endif\nINCLUDE_ASM("asm/nonmatchings/main/a", funcA);\n')
        r = self.run_progress()
        self.assertIn("main: 64/128 bytes (50.0%), 2 functions in asm", r.stdout)

    def test_handwritten_asm_excluded(self):
        y = (self.d / "roguesquadron.yaml").read_text().replace("[0x1060, asm, \"main/b\"]", "[0x1060, hasm, \"main/b\"]")
        (self.d / "roguesquadron.yaml").write_text(y)
        r = self.run_progress()
        self.assertEqual(r.returncode, 0, r.stderr)
        self.assertIn("main: 64/96 bytes (66.7%), 1 functions in asm", r.stdout)
        self.assertIn("total: 128/160 bytes (80.0%), 1 functions in asm", r.stdout)

if __name__ == "__main__":
    unittest.main()
