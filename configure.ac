AC_PREREQ([2.69])

AC_INIT([fetch-complete], [0.1], [ehostunreach@gmail.com],
        [fetch-complete], [https://github.com/ehostunreach/fetch-complete])

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE([foreign subdir-objects])
AC_PROG_CC
AM_PROG_CC_C_O
AM_PROG_AR
AC_PROG_INSTALL

AC_ARG_WITH([llvm-prefix],
    [AS_HELP_STRING([--with-llvm-prefix],
        [Prefix for LLVM installations in non-standard locations])],
    [llvm_prefix="$withval"],
    [llvm_prefix=""])

AC_PATH_PROG([LLVM_CONFIG], [llvm-config], [no], ["$llvm_prefix/bin"])
if test -x $LLVM_CONFIG; then
    CLANG_CFLAGS=`$LLVM_CONFIG --cflags`
    CLANG_LDFLAGS="`$LLVM_CONFIG --ldflags` -lclang"
    AC_SUBST([CLANG_CFLAGS])
    AC_SUBST([CLANG_LDFLAGS])
else
    AC_MSG_ERROR([Can not find llvm-config. Please, specify the llvm-prefix])
fi

PKG_CHECK_MODULES([DEPS],
                  [glib-2.0 >= 2.36, libsoup-2.4 >= 2.26, json-glib-1.0 >= 0.14])


AC_CONFIG_FILES([Makefile])
AC_OUTPUT
