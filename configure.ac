AC_INIT([amhello], [1.0], [bug-automake@gnu.org])

AC_PROG_CC
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile src/Makefile])

AM_INIT_AUTOMAKE([-Wall -Werror foreign])
PKG_CHECK_MODULES([libsoup], [libsoup-2.4 >= 2.26])
AM_PROG_CC_C_O

AC_OUTPUT

