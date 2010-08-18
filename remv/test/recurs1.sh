#!/bin/sh

rm -fr tmp/
mkdir -p tmp/tmp2
touch tmp/tmp2/asdf
$top_builddir/src/remv  a b tmp/ >/dev/null 2>&1
test -f tmp/tmp2/asdf && test ! -f tmp/tmp2/bsdf
status=$?
rm -fr tmp/
exit $status

