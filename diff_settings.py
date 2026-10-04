def apply(config, args):
    config["baseimg"] = "rogue_squadron.z64"
    config["myimg"] = "build/tyler.z64"
    config["mapfile"] = "build/tyler.elf.map"
    config["source_directories"] = ["src", "include"]
    config["arch"] = "mips"
    config["objdump_executable"] = "mips-linux-gnu-objdump"
    config["make_command"] = ["make", "-j16"]
