AC_INIT([autocomplete], [1.0], [ehostunreach@gmail.com])

AC_PROG_CC
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile src/Makefile])
AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects])
PKG_CHECK_MODULES([glib], [glib-2.0 >= 2.36])
PKG_CHECK_MODULES([libsoup], [libsoup-2.4 >= 2.26])
PKG_CHECK_MODULES([json_glib], [json-glib-1.0 >= 0.14])
AM_PROG_CC_C_O
AM_PROG_AR

LT_INIT

AC_OUTPUT

