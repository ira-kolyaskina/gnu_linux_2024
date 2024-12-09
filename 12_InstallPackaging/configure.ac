#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([Guessing game], [1.0.0], [ira.koliaskina@gmail.com], [guess])
AC_CONFIG_SRCDIR([src/guess.c])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([foreign subdir-objects])
DX_INIT_DOXYGEN([guess])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([libintl.h locale.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_CHECK_FUNCS([setlocale strcasecmp])

AC_CONFIG_FILES([Makefile src/Makefile Doxyfile])
AC_OUTPUT