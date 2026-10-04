#!/bin/sh
# Runs decomp-permuter on each function in a list, stopping a run at score 0, after PLATEAU seconds without a new best, or at MAX seconds.
# Usage (from the worktree root): perm_batch2.sh <list file> <plateau seconds> <max seconds> <jobs>
LIST="$1"; PLATEAU="$2"; MAX="$3"; JOBS="$4"
OUT="$HOME/rs64-auto/perm_results.tsv"
best_of() { ls "$1" 2>/dev/null | grep -oE "^output-[0-9]+" | sed "s/output-//" | sort -n | head -1; }
for f in $(cat "$LIST"); do
    grep -rq "INCLUDE_ASM(\"[^\"]*\", $f)" src || continue
    grep -q "^$f	" "$OUT" 2>/dev/null && continue
    dir="tools/decomp-permuter/nonmatchings/$f"
    rm -rf "$dir"
    snip=""
    [ -f "$HOME/rs64-auto/snippets/$f.c" ] && snip="--snippet $HOME/rs64-auto/snippets/$f.c"
    python3 tools/perm_import.py "$f" $snip > "$HOME/rs64-auto/perm_import_$f.log" 2>&1
    if [ ! -f "$dir/base.c" ]; then
        printf "%s\timport-failed\t-\n" "$f" >> "$OUT"; continue
    fi
    (cd tools/decomp-permuter && exec python3 permuter.py "nonmatchings/$f" -j"$JOBS" --stop-on-zero > "$HOME/rs64-auto/perm_$f.log" 2>&1) &
    pid=$!
    start=$(date +%s); last=$start; best=""
    reason="max"
    while kill -0 $pid 2>/dev/null; do
        sleep 15
        now=$(date +%s)
        b=$(best_of "$dir")
        if [ -n "$b" ] && { [ -z "$best" ] || [ "$b" -lt "$best" ]; }; then best=$b; last=$now; fi
        [ "$best" = "0" ] && { reason="zero"; break; }
        [ $((now - last)) -ge "$PLATEAU" ] && { reason="plateau"; break; }
        [ $((now - start)) -ge "$MAX" ] && break
    done
    pkill -P $pid 2>/dev/null; kill $pid 2>/dev/null; wait $pid 2>/dev/null
    b=$(best_of "$dir"); [ -n "$b" ] && best=$b
    base=$(tr "\r" "\n" < "$HOME/rs64-auto/perm_$f.log" | grep -oE "base score = [0-9]+" | head -1 | grep -oE "[0-9]+$")
    printf "%s\tbest=%s\tbase=%s\tstop=%s\tsecs=%s\n" "$f" "${best:--}" "${base:--}" "$reason" "$(( $(date +%s) - start ))" >> "$OUT"
done
