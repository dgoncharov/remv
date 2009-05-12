# "Id:"                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.
AC_PREREQ([2.63])
AC_INIT([FULL-PACKAGE-NAME], [VERSION], [BUG-REPORT-ADDRESS])
AM_INIT_AUTOMAKE([remv], [0.11]) 
AC_CONFIG_SRCDIR([remv.cpp])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC
AC_PROG_CXX
AC_PROG_RANLIB
AC_LANG_CPLUSPLUS

AC_HEADER_STDBOOL

AC_MSG_CHECKING([for boost/regex.hpp])
AC_COMPILE_IFELSE([
#include <boost/regex.hpp>
],
    [AC_MSG_RESULT([yes])],
    [AC_MSG_RESULT([no])
     AC_MSG_ERROR([boost/regex.hpp not found. The boost libraries can be obtained from boost.org])]
)

#TODO: check filesystem version
AC_MSG_CHECKING([for boost/filesystem.hpp])
AC_COMPILE_IFELSE([
#include <boost/filesystem.hpp>
],
    [AC_MSG_RESULT([yes])],
    [AC_MSG_RESULT([no])
     AC_MSG_ERROR([boost/filesystem.hpp not found. The boost libraries can be obtained from boost.org])]
)

AC_MSG_CHECKING([for boost/program_options.hpp])
AC_COMPILE_IFELSE([
#include <boost/program_options.hpp>
],
    [AC_MSG_RESULT([yes])],
    [AC_MSG_RESULT([no])
     AC_MSG_ERROR([boost/program_options.hpp not found. The boost libraries can be obtained from boost.org])]
)

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
     AC_MSG_ERROR([Can't find the boost_regex library. The boost libraries can be obtained from boost.org])]
)
LIBS="$save_LIBS"

save_LIBS="$LIBS"
LIBS="$LIBS -lboost_filesystem"
AC_MSG_CHECKING([for boost.filesystem library])
AC_LINK_IFELSE([
#include <boost/filesystem.hpp>
int main() {boost::filesystem::path r(""); return 0;}
],
    [AC_MSG_RESULT([-lboost_filesystem])],
    [AC_MSG_RESULT([not found])
     AC_MSG_ERROR([Can't find the boost_filesystem library. The boost libraries can be obtained from boost.org])]
)

save_LIBS="$LIBS"
LIBS="$LIBS -lboost_program_options"
AC_MSG_CHECKING([for boost.program_options library])
AC_LINK_IFELSE([
#include <boost/program_options.hpp>
int main() {boost::program_options::options_description r(""); return 0;}
],
    [AC_MSG_RESULT([-lboost_program_options])],
    [AC_MSG_RESULT([not found])
     AC_MSG_ERROR([Can't find the boost_program_options library. The boost libraries can be obtained from boost.org])]
)
LIBS="$save_LIBS"

LIBS="-lboost_regex -lboost_filesystem -lboost_program_options $LIBS"

AC_CONFIG_FILES([Makefile])

AC_OUTPUT

