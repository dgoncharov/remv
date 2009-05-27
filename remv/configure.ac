# "Id:"                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.
AC_PREREQ([2.63])
AC_INIT([FULL-PACKAGE-NAME], [VERSION], [BUG-REPORT-ADDRESS])
AM_INIT_AUTOMAKE([remv], [0.12]) 
AC_CONFIG_SRCDIR([remv.cpp])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC
AC_PROG_CXX
AC_PROG_RANLIB
AC_LANG_CPLUSPLUS

AC_HEADER_STDBOOL

AC_CHECK_HEADERS([\
    cstdio string iostream stdexcept],,
    AC_MSG_ERROR([You need to have the C++ standard headers installed]))

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
    CXXFLAGS="$CXXFLAGS -D_DEBUG -O0 -g -Wall -Werror"
else
    AC_DEFINE(NDEBUG,, [Disable debugging])
    CXXFLAGS="$CXXFLAGS -DNDEBUG -Wall -Werror"
fi

AC_CONFIG_FILES([Makefile])

AC_OUTPUT

