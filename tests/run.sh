#!/usr/bin/env bash
# Compile each examples/inputN.in and compare the result with examples/pcodeN.txt.
# Blank lines, CRLF endings and `sep` lines are ignored: the compiler emits a safe
# upper bound for the expression-stack size (sep 50) instead of the exact depth.
set -u
cd "$(dirname "$0")/.."

normalize() { tr -d '\r' < "$1" | sed 's/[[:space:]]*$//' | grep -v '^$' | grep -v '^sep '; }

pass=0 fail=0 tmp=$(mktemp -d)
trap 'rm -rf "$tmp"' EXIT
for expected in examples/pcode*.txt; do
    n=${expected//[^0-9]/}
    input=examples/input$n.in
    (cd "$tmp" && "$OLDPWD/pcodeGen" "$OLDPWD/$input" >/dev/null 2>&1)
    if diff <(normalize "$tmp/outputFile.txt") <(normalize "$expected") >/dev/null; then
        echo "PASS  $input"; pass=$((pass + 1))
    else
        echo "FAIL  $input"; fail=$((fail + 1))
    fi
done
echo "$pass passed, $fail failed"
[ "$fail" -eq 0 ]
