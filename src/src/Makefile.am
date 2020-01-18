defsdir = $(datadir)/pygtk/2.0/defs
defs_DATA = pynotify.defs

INCLUDES = \
	-DG_LOG_DOMAIN=\"pynotify-python\" \
	-DDATADIR=\"$(datadir)\" \
	-DLIBDIR=\"$(libdir)\" \
	$(NOTIFY_PYTHON_CFLAGS) \
	$(PYTHON_INCLUDES)

pkgpythondir = $(pyexecdir)/gtk-2.0
pkgpyexecdir = $(pyexecdir)/gtk-2.0

pkgpypynotifydir = $(pkgpythondir)/pynotify
pkgpypynotify_PYTHON = __init__.py

pypynotifydir = $(pkgpyexecdir)/pynotify
pypynotify_LTLIBRARIES = _pynotify.la

_pynotify_la_LDFLAGS = -module -avoid-version -export-symbols-regex init_pynotify
_pynotify_la_LIBADD = $(NOTIFY_PYTHON_LIBS)
_pynotify_la_SOURCES = pynotifymodule.c pynotify.c
#nodist_pynotify_la_SOURCES = pynotify.c

CLEANFILES = pynotify.c
EXTRA_DIST = pynotify.override $(defs_DATA)
pynotify.c: $(defs_DATA) pynotify.override

%.c: %.defs
	(cd $(srcdir) \
	 && $(PYGTK_CODEGEN) \
		--register $(PYGTK_DEFSDIR)/gtk-types.defs \
		--register $(PYGTK_DEFSDIR)/gdk-types.defs \
	    --override $*.override \
	    --prefix py$* $*.defs) > gen-$*.c \
	 && cp gen-$*.c $*.c \
	 && rm -f gen-$*.c

DEFHEADERS = $(wildcard $(includedir)/libnotify/*.h)

update-defs:
	@python $(datadir)/pygtk/2.0/codegen/h2def.py $(DEFHEADERS) > pynotify.defs.tmp
	@sed -e 's/define-function notify_\(init\|uninit\|is_\|get\)/define-function \1/g' \
	     -e '/define-function notify_notification_new/,/^$$/ { s/\("message"\)/\1 (null-ok) (default "NULL")/g; s/\("icon"\)/\1 (null-ok) (default "NULL")/g; s/\("attach"\)/\1 (null-ok) (default "NULL")/g; }' \
	     -e '/define-method update/,/^$$/ { s/\("message"\)/\1 (null-ok) (default "NULL")/g; s/\("icon"\)/\1 (null-ok) (default "NULL")/g; }' \
	     pynotify.defs.tmp > pynotify.defs
	@rm -f pynotify.defs.tmp
	@echo Definitions updated
