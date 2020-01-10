AC_INIT(notify-python, 0.1.1, chipx86@chipx86.com)
AC_PREREQ(2.50)
AC_CONFIG_SRCDIR(config.h.in)
AC_COPYRIGHT([Copyright 2006 Christian Hammond])

PACKAGE=notify-python
VERSION=0.1.1

AM_INIT_AUTOMAKE($PACKAGE, $VERSION)
AM_CONFIG_HEADER(config.h)

PYGTK_REQUIRED=2.4.0
LIBNOTIFY_REQUIRED=0.4.3

AC_PROG_CC
AC_DISABLE_STATIC
AC_PROG_LIBTOOL

AM_PATH_PYTHON(2.3.5)
AM_CHECK_PYTHON_HEADERS(,[AC_MSG_ERROR(could not find Python headers)])

PKG_CHECK_MODULES(NOTIFY_PYTHON, [pygtk-2.0 >= $PYGTK_REQUIRED
                                  libnotify >= $LIBNOTIFY_REQUIRED])
AC_SUBST(NOTIFY_PYTHON_CFLAGS)
AC_SUBST(NOTIFY_PYTHON_LIBS)

AC_MSG_CHECKING(for pygtk defs)
PYGTK_DEFSDIR=`$PKG_CONFIG --variable=defsdir pygtk-2.0`
AC_SUBST(PYGTK_DEFSDIR)
AC_MSG_RESULT($PYGTK_DEFSDIR)

AC_MSG_CHECKING(for pygtk codegen)
PYGTK_CODEGEN="$PYTHON `$PKG_CONFIG --variable=codegendir pygtk-2.0`/codegen.py"
AC_SUBST(PYGTK_CODEGEN)
AC_MSG_RESULT($PYGTK_CODEGEN)

AC_CONFIG_FILES([
notify-python.pc
Makefile
src/Makefile
tests/Makefile
])

AC_OUTPUT

echo
echo $PACKAGE v$VERSION
echo
echo "Now type make to compile"
echo "Then su to root and type: make install"
echo
