#!/bin/sh

mkdir -p config &&
aclocal &&
autoheader &&
automake --add-missing &&
autoconf


