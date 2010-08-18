#!/bin/sh

rm -fr tmp/
mkdir -p tmp
touch tmp/asdf
$top_builddir/src/remv a b tmp/ >/dev/null 2>&1
test -f tmp/bsdf
status=$?
rm -fr tmp/
exit $status

