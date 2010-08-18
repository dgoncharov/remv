#!/bin/sh

rm -fr tmp/
mkdir -p tmp
touch tmp/1
$top_builddir/src/remv 1 2 tmp/ >/dev/null 2>&1
test -f tmp/2
status=$?
rm -fr tmp/
exit $status

