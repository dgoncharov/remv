# "Id:"                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.
AC_PREREQ([2.62])
AC_INIT([remv], 0.20, [dgoncharov@users.sf.net])
AC_CONFIG_AUX_DIR(config)
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([src/remv.cpp])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC
AC_PROG_CXX
AC_LANG_CPLUSPLUS

AC_HEADER_STDBOOL

AC_CHECK_FUNCS([strerror])

AC_CHECK_HEADERS([\
    cerrno cstdio string iostream stdexcept],,
    AC_MSG_ERROR([You need to have the C++ standard headers installed]))

AC_ARG_WITH(boost,
AC_HELP_STRING(
    [--with-boost=prefix],
    [boost install directory]),
    boost_pathset=yes,
    boost_pathset=no)

if test $boost_pathset = yes ; then
    CPPFLAGS="$CPPFLAGS -I$with_boost/include"
    LDFLAGS="$LDFLAGS -L$with_boost/lib"
fi

BOOST_NOT_FOUND_ERRMSG="You need to install the boost libraries. The boost libraries can be obtained from boost.org"

AC_CHECK_HEADERS([ \
    boost/filesystem.hpp \
    boost/regex.hpp \
    boost/program_options.hpp],,
    AC_MSG_ERROR([You need to have the boost headers installed]))

AC_MSG_CHECKING([for boost version])
AC_COMPILE_IFELSE([
#define BOOST_MIN_VERSION 103700
#include <boost/version.hpp>
#if BOOST_VERSION < BOOST_MIN_VERSION
#error this version of boost is not supported
#endif
],
    [AC_MSG_RESULT([yes])],
    [AC_MSG_RESULT([no])
     AC_MSG_ERROR([Your version of the boost libraries is not supported. Update your boost libraries to at least 1_37. The boost libraries can be obtained from boost.org])]
)

save_LIBS="$LIBS"
LIBS="$LIBS -lboost_regex"
AC_MSG_CHECKING([for boost.regex library])
AC_LINK_IFELSE([
#include <boost/regex.hpp>
int main() {boost::regex r(""); return 0;}
],
    [AC_MSG_RESULT([-lboost_regex])],
    [AC_MSG_RESULT([not found])
     AC_MSG_ERROR([Can't find the boost_regex library. $BOOST_NOT_FOUND_ERRMSG])]
)
LIBS="$save_LIBS -lboost_regex"

save_LIBS="$LIBS"
LIBS="$LIBS -lboost_filesystem"
AC_MSG_CHECKING([for boost.filesystem library])
AC_LINK_IFELSE([
#include <boost/filesystem.hpp>
int main() {boost::filesystem::path r(""); return 0;}
],
    [AC_MSG_RESULT([-lboost_filesystem])],
    [AC_MSG_RESULT([not found])
     AC_MSG_ERROR([Can't find the boost_filesystem library. $BOOST_NOT_FOUND_ERRMSG])]
)
LIBS="$save_LIBS -lboost_filesystem"

save_LIBS="$LIBS"
LIBS="$LIBS -lboost_program_options"
AC_MSG_CHECKING([for boost.program_options library])
AC_LINK_IFELSE([
#include <boost/program_options.hpp>
int main() {boost::program_options::options_description r(""); return 0;}
],
    [AC_MSG_RESULT([-lboost_program_options])],
    [AC_MSG_RESULT([not found])
     AC_MSG_ERROR([Can't find the boost_program_options library. $BOOST_NOT_FOUND_ERRMSG])]
)
LIBS="$save_LIBS -lboost_program_options"


AH_TOP([
#ifndef CONFIG_H
#define CONFIG_H])
AH_BOTTOM([#endif /* CONFIG_H */])
CXXFLAGS="$CXXFLAGS -include config.h"

AC_MSG_CHECKING(whether to build with debug information)
debuger=no
AC_ARG_ENABLE(
    debug,
    AC_HELP_STRING([--enable-debug],[enable debugging (def=no)]),
    debuger="$enableval")
AC_MSG_RESULT($debuger)

if test x"$debuger" = x"yes"; then
    AC_DEFINE(_DEBUG,, [Enable debugging])
    CXXFLAGS=`echo $CXXFLAGS | sed -e "s/-O@<:@0-3@:>@//g; s/-Os//g; s/-fomit-frame-pointer//g"`
    CXXFLAGS="$CXXFLAGS -O0 -g -Wall -Werror"
else
    AC_DEFINE(NDEBUG,, [Disable debugging])
    CXXFLAGS="$CXXFLAGS -Wall -Werror"
fi

AC_CONFIG_FILES([Makefile src/Makefile doc/Makefile doc/remv.1])

AC_OUTPUT

