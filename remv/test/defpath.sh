#!/bin/sh

rm -fr tmp/
mkdir -p tmp
touch tmp/1
cd tmp
../$top_builddir/src/remv 1 2 >/dev/null 2>&1
test -f 2
status=$?
cd ..
rm -fr tmp/
exit $status

