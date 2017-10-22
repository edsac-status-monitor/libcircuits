#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

# require autoconf 2.69 or newer
AC_PREREQ([2.69])

# project metadata
AC_INIT([libnetworking], [0.0.1], [eddie@ellams.net])

# put auxiliary files in subdirectories to reduce clutter
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([build-aux])

# sanity check. At least this should exist
AC_CONFIG_SRCDIR([./src/vector.c])

# use automake
# std-options: executables should have --version and --help
# subdir-objects: put objects in the same subdir as the source file
# foreign: don't force complience with GNU standards
# silent-rules: be quiet
AM_INIT_AUTOMAKE
AC_CONFIG_FILES([Makefile
                 src/Makefile
                 tests/Makefile])

# generate include/config.h
AC_CONFIG_HEADERS([./include/config.h])


# Checks for programs.
AC_PROG_CC
AC_PROG_AWK
# for making static libraries:
AM_PROG_AR

# Initialise autotools
LT_INIT

# Checks for header files.
AC_CHECK_HEADERS([])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_FUNC_STRTOD
AC_CHECK_FUNCS([memset])

PKG_CHECK_MODULES([CHECK], [check >= 0.9.4])

AC_OUTPUT
