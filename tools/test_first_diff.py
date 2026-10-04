import unittest, tempfile, pathlib, subprocess, sys
HERE = pathlib.Path(__file__).parent

def run(a, b, mapfile=None):
    cmd = [sys.executable, str(HERE / "first_diff.py"), str(a), str(b)]
    if mapfile:
        cmd += ["--map", str(mapfile)]
    return subprocess.run(cmd, capture_output=True, text=True)

MAP = """
.main           0x0000000080000400    0xa4d30 load address 0x0000000000001000
 .text         0x0000000080000400       0x40 build/asm/header.o
                0x0000000080000400                header_sym
 .text          0x0000000080000440      0x100 build/src/main/02490.o
                0x0000000080000440                funcA
                0x00000000800004a0                funcB
"""

class T(unittest.TestCase):
    def setUp(self):
        self.d = pathlib.Path(tempfile.mkdtemp())
        self.good = self.d / "good.z64"
        self.good.write_bytes(bytes(range(256)) * 32)
        (self.d / "m.map").write_text(MAP)

    def flipped(self, off):
        bad = self.d / "bad.z64"
        data = bytearray(self.good.read_bytes()); data[off] ^= 0xFF
        bad.write_bytes(bytes(data))
        return bad

    def test_match(self):
        r = run(self.good, self.good)
        self.assertEqual(r.returncode, 0)
        self.assertIn("MATCH", r.stdout)

    def test_byte_flip_reports_offset(self):
        r = run(self.flipped(0x10), self.good)
        self.assertEqual(r.returncode, 1)
        self.assertIn("0x10", r.stdout)
        self.assertIn("header", r.stdout)
        self.assertIn("1 differing byte", r.stdout)

    def test_size_mismatch(self):
        short = self.d / "short.z64"
        short.write_bytes(self.good.read_bytes()[:1000])
        r = run(short, self.good)
        self.assertEqual(r.returncode, 1)
        self.assertIn("size", r.stdout.lower())

    def test_map_names_function(self):
        r = run(self.flipped(0x1000 + 0xA4), self.good, self.d / "m.map")
        self.assertIn("funcB", r.stdout)
        self.assertIn("0x800004A4", r.stdout)

    def test_overlay_offset(self):
        big = self.d / "big.z64"
        big.write_bytes(bytes(0x110000))
        bad = self.d / "bigbad.z64"
        data = bytearray(big.read_bytes()); data[0x10C2D0 + 0x20] = 1
        bad.write_bytes(bytes(data))
        r = run(bad, big)
        self.assertIn("menu_overlay", r.stdout)
        self.assertIn("vram 0x800A5150", r.stdout)

    def test_overlay_symbol_from_own_section(self):
        ovl_map = """
.mission_overlay
                0x00000000800a5130    0x665a0 load address 0x00000000000a5d30
 .text          0x00000000800a5130      0x100 build/src/mission_overlay/0AA780.o
                0x00000000800a5130                missionFunc
.menu_overlay   0x00000000800a5130    0x283f0 load address 0x000000000010c2d0
 .text          0x00000000800a5130      0x100 build/src/menu_overlay/110410.o
                0x00000000800a5140                menuFunc
.menu_overlay_bss
                0x00000000800cd520     0x2ec0
                0x00000000800a5148                menuBssSym
"""
        (self.d / "ovl.map").write_text(ovl_map)
        big = self.d / "big.z64"
        big.write_bytes(bytes(0x110000))
        bad = self.d / "bigbad.z64"
        data = bytearray(big.read_bytes()); data[0x0A5D30 + 0x20] = 1
        bad.write_bytes(bytes(data))
        r = run(bad, big, self.d / "ovl.map")
        self.assertIn("mission_overlay", r.stdout)
        self.assertIn("in missionFunc +0x20", r.stdout)

if __name__ == "__main__":
    unittest.main()
