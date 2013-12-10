AC_INIT([FetchComplete], [0.1], [ehostunreach@gmail.com])

CFLAGS="-Wall -Wextra -g -O0"
AC_PROG_CC
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile src/Makefile])
AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE([foreign subdir-objects])
PKG_CHECK_MODULES([glib], [glib-2.0 >= 2.36])
PKG_CHECK_MODULES([libsoup], [libsoup-2.4 >= 2.26])
PKG_CHECK_MODULES([json_glib], [json-glib-1.0 >= 0.14])

AM_PROG_CC_C_O
AM_PROG_AR

AC_ARG_WITH([llvm-prefix],
    [AS_HELP_STRING([--with-llvm-prefix],
        [Prefix for LLVM installations in non-standard locations])],
    [llvm_prefix="$withval"],
    [llvm_prefix=""])

AC_PATH_PROG([LLVM_CONFIG], [llvm-config], [no], ["$llvm_prefix/bin"])

if test -x $LLVM_CONFIG; then
    CLANG_CFLAGS=`$LLVM_CONFIG --cflags`
    CLANG_LDFLAGS="`$LLVM_CONFIG --ldflags` -lclang"

else
    AC_MSG_ERROR([Can not find llvm-config. Please, specify the llvm-prefix])
fi

AC_SUBST([CLANG_CFLAGS])
AC_SUBST([CLANG_LDFLAGS])

LT_INIT
AC_OUTPUT
