#!/bin/sh

rm -fr tmp/
mkdir -p tmp
touch tmp/-asdf
$top_builddir/src/remv \\-as \\-bz tmp/ >/dev/null 2>&1
test -f tmp/-bzdf
status=$?
rm -fr tmp/
exit $status

