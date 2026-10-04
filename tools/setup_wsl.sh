#!/bin/sh
# Builds a user-local toolchain for the decomp (no sudo): MIPS binutils/cpp from the Ubuntu cross packages, wibo, and a Python venv with splat.
set -e
TOOLS="$(cd "$(dirname "$0")" && pwd)"
OPT="$HOME/opt"
mkdir -p "$OPT/mips/debs"
cd "$OPT/mips/debs"
apt-get download binutils-mips-linux-gnu cpp-mips-linux-gnu cpp-12-mips-linux-gnu
for d in *.deb; do dpkg -x "$d" "$OPT/mips/root"; done
if [ ! -x "$OPT/rs64venv/bin/pip" ]; then
    python3 -m venv --without-pip "$OPT/rs64venv"
    curl -sSL https://bootstrap.pypa.io/get-pip.py | "$OPT/rs64venv/bin/python" - -q
fi
"$OPT/rs64venv/bin/pip" install -q "splat64[mips]"
cat > "$OPT/rs64env.sh" <<ENV
export PATH=\$HOME/opt/mips/root/usr/bin:\$HOME/opt/rs64venv/bin:\$PATH
export LD_LIBRARY_PATH=\$HOME/opt/mips/root/usr/lib/x86_64-linux-gnu\${LD_LIBRARY_PATH:+:\$LD_LIBRARY_PATH}
ENV
cd "$TOOLS"
if [ ! -x wibo-x86_64 ]; then
    curl -sSL -o wibo-x86_64 https://github.com/decompals/wibo/releases/download/1.2.0/wibo-x86_64
    chmod +x wibo-x86_64
fi
echo "Run: . ~/opt/rs64env.sh"
