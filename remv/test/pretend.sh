#!/bin/sh

rm -fr tmp/
mkdir -p tmp
touch tmp/asdf
$top_builddir/src/remv -p a b tmp/ >/dev/null 2>&1
test -f tmp/asdf && test ! -f bsdf
status=$?
rm -fr tmp/
exit $status

