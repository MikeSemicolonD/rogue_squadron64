#!/bin/sh
# Builds a user-local toolchain for the decomp (no sudo): MIPS binutils/cpp from the Ubuntu cross packages, wibo, and a Python venv with splat.
set -e
TOOLS="$(cd "$(dirname "$0")" && pwd)"
OPT="$HOME/opt"
WIBO_URL="${WIBO_URL:-https://github.com/decompals/wibo/releases/download/1.2.0/wibo-x86_64}"
mkdir -p "$OPT/mips/debs"
cd "$OPT/mips/debs"
rm -f ./*.deb
if ! apt-get download binutils-mips-linux-gnu cpp-mips-linux-gnu cpp-12-mips-linux-gnu; then
    echo "apt-get download failed; run 'sudo apt-get update' once and retry." >&2
    exit 1
fi
for d in *.deb; do dpkg -x "$d" "$OPT/mips/root"; done
if [ ! -x "$OPT/rs64venv/bin/pip" ]; then
    python3 -m venv --without-pip "$OPT/rs64venv"
    curl -fsSL https://bootstrap.pypa.io/get-pip.py | "$OPT/rs64venv/bin/python" - -q
fi
"$OPT/rs64venv/bin/pip" install -q "splat64[mips]==0.41.1"
cat > "$OPT/rs64env.sh" <<ENV
export PATH=\$HOME/opt/mips/root/usr/bin:\$HOME/opt/rs64venv/bin:\$PATH
export LD_LIBRARY_PATH=\$HOME/opt/mips/root/usr/lib/x86_64-linux-gnu\${LD_LIBRARY_PATH:+:\$LD_LIBRARY_PATH}
ENV
. "$OPT/rs64env.sh"
for t in mips-linux-gnu-as mips-linux-gnu-ld mips-linux-gnu-cpp; do
    if ! "$t" --version >/dev/null 2>&1; then
        echo "$t does not run; missing host libraries (install them with sudo apt-get install):" >&2
        ldd "$(command -v "$t")" "$OPT"/mips/root/usr/libexec/gcc-cross/mips-linux-gnu/*/cc1 2>/dev/null | grep "not found" >&2 || true
        exit 1
    fi
done
cd "$TOOLS"
if [ ! -x wibo-x86_64 ]; then
    curl -fsSL -o wibo-x86_64.part "$WIBO_URL" || { rm -f wibo-x86_64.part; echo "wibo download failed: $WIBO_URL" >&2; exit 1; }
    chmod +x wibo-x86_64.part
    mv wibo-x86_64.part wibo-x86_64
fi
echo "Run: . ~/opt/rs64env.sh"
