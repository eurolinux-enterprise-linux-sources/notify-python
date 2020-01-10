#include <pygobject.h>
#include <pygtk/pygtk.h>
#include <libnotify/notify.h>

void pynotify_register_classes(PyObject *d);
extern PyMethodDef pypynotify_functions[];

DL_EXPORT(void)
init_pynotify(void)
{
	PyObject *m, *d;

	init_pygobject();
	init_pygtk();

	m = Py_InitModule("pynotify._pynotify", pypynotify_functions);
	d = PyModule_GetDict(m);

	pypynotify_register_classes(d);
	pypynotify_add_constants(m, "NOTIFY_");
	PyModule_AddObject(m, "EXPIRES_DEFAULT",
					   PyInt_FromLong(NOTIFY_EXPIRES_DEFAULT));
	PyModule_AddObject(m, "EXPIRES_NEVER",
					   PyInt_FromLong(NOTIFY_EXPIRES_NEVER));

	if (PyErr_Occurred()) {
		Py_FatalError("can't initialize module pynotify");
	}
}
