#!/bin/sh

rm -fr tmp/
mkdir -p tmp
touch tmp/AaBbCc
$top_builddir/src/remv "(\w+)" "\L\\1" tmp/ >/dev/null 2>&1
test -f tmp/aabbcc
status=$?
rm -fr tmp/
exit $status

