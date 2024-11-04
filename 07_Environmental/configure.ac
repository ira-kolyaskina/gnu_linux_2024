#                                               -*- Autoconf -*-
# Этот файл обрабатывается autoconf для создания скрипта конфигурации.

AC_PREREQ([2.71])
AC_INIT([FULL-PACKAGE-NAME], [VERSION], [BUG-REPORT-ADDRESS])
AM_INIT_AUTOMAKE([foreign subdir-objects])
AC_CONFIG_SRCDIR([rhasher.c])
AC_CONFIG_HEADERS([config.h])

AC_PROG_CC

AC_CHECK_LIB([rhash], [rhash_library_init], [], 
    [AC_MSG_ERROR([Не удалось найти символ rhash_library_init!])])

AC_ARG_WITH([readline],
    [AS_HELP_STRING([--without-readline], [отключить поддержку readline])],
    [],
    [with_readline=yes])

AS_IF([test "x$with_readline" != xno], 
    [AC_CHECK_LIB([readline], [readline],
        [
            AC_SUBST([rhasher_LDADD], ["-lreadline"])
            AC_DEFINE([READLINE], [1], [Мы хотим использовать readline])
        ],
        [
            AC_MSG_FAILURE([Не удалось найти библиотеку readline (используйте --without-readline)])
        ])])

AC_CHECK_HEADER([rhash.h])
AS_IF([test "x$with_readline" != xno],
    [AC_CHECK_HEADER([readline/readline.h])])

AC_TYPE_SIZE_T

AC_CHECK_FUNCS([strerror strstr])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
