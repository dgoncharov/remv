#!/bin/sh

rm -fr tmp/
mkdir -p tmp
touch tmp/asdf tmp/qwer tmp/azxc
$top_builddir/src/remv a b tmp/ >/dev/null 2>&1
test -f tmp/bsdf && test tmp/qwer && test tmp/bzxc
status=$?
rm -fr tmp/
exit $status

