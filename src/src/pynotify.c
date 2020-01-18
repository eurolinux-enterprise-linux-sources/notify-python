/* -- THIS FILE IS GENERATED - DO NOT EDIT *//* -*- Mode: C; c-basic-offset: 4 -*- */

#include <Python.h>



#line 3 "pynotify.override"
#include <Python.h>
#include <libnotify/notify.h>
#include "pygobject.h"

typedef struct
{
	PyGObject *notification;
	PyObject *callback;
	PyObject *user_data;

} ActionCbData;

static PyObject *
pygalago_wrap_str_list(GList *list)
{
	GList *l;
	PyObject *item, *ret;

	ret = PyList_New(0);

	if (ret == NULL)
		return NULL;

	for (l = list; l != NULL; l = l->next)
	{
		item = PyString_FromString((char *)l->data);

		if (item == NULL)
		{
			Py_DECREF(ret);
			return NULL;
		}

		PyList_Append(ret, item);
		Py_DECREF(item);
	}

	return ret;
}

static PyObject *
pygalago_wrap_gobj_list(GList *list)
{
	GList *l;
	PyObject *item, *ret;

	ret = PyList_New(0);

	if (ret == NULL)
		return NULL;

	for (l = list; l != NULL; l = l->next)
	{
		item = pygobject_new((GObject *)l->data);

		if (item == NULL)
		{
			Py_DECREF(ret);
			return NULL;
		}

		PyList_Append(ret, item);
		Py_DECREF(item);
	}

	return ret;
}

GList *
pygalago_unwrap_gobj_list(PyObject *py_items, PyTypeObject *type,
						  gboolean *ok)
{
	int len, i;
	GList *items;

	*ok = TRUE;

	len = PyList_Size(py_items);

	for (i = 0; i < len; i++)
	{
		PyObject *item = PyList_GetItem(py_items, i);

		if (!pygobject_check(item, type))
		{
			char *err = g_strdup_printf("list item not a %s", type->tp_name);

			PyErr_SetString(PyExc_TypeError, err);

			g_free(err);
			g_list_free(items);
			*ok = FALSE;
			return NULL;
		}

		items = g_list_append(items, pygobject_get(item));
	}

	return items;
}

static void
_notify_action_cb(NotifyNotification *n, const char *action,
				  ActionCbData *data)
{
	PyGILState_STATE state;
	PyObject *args;

	state = pyg_gil_state_ensure();

	if (data->user_data == Py_None)
	{
		args = Py_BuildValue("Os", data->notification, action);
	}
	else
	{
		args = Py_BuildValue("OsO", data->notification, action,
							 data->user_data);
	}

	PyEval_CallObject(data->callback, args);
	Py_DECREF(args);
	pyg_gil_state_release(state);
}

static void
_action_cb_data_destroy(ActionCbData *data)
{
	Py_DECREF(data->callback);
	g_free(data);
}
#line 140 "pynotify.c"


/* ---------- types from other modules ---------- */
static PyTypeObject *_PyGObject_Type;
#define PyGObject_Type (*_PyGObject_Type)
static PyTypeObject *_PyGdkPixbuf_Type;
#define PyGdkPixbuf_Type (*_PyGdkPixbuf_Type)
static PyTypeObject *_PyGtkWidget_Type;
#define PyGtkWidget_Type (*_PyGtkWidget_Type)
static PyTypeObject *_PyGtkStatusIcon_Type;
#define PyGtkStatusIcon_Type (*_PyGtkStatusIcon_Type)


/* ---------- forward type declarations ---------- */
PyTypeObject PyNotifyNotification_Type;

#line 157 "pynotify.c"



/* ----------- NotifyNotification ----------- */

static int
_wrap_notify_notification_new(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "summary", "message", "icon", "attach", NULL };
    char *summary, *message = NULL, *icon = NULL;
    PyGObject *py_attach = NULL;
    GtkWidget *attach = NULL;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "s|zzO:NotifyNotification.__init__", kwlist, &summary, &message, &icon, &py_attach))
        return -1;
    if ((PyObject *)py_attach == Py_None)
        attach = NULL;
    else if (py_attach && pygobject_check(py_attach, &PyGtkWidget_Type))
        attach = GTK_WIDGET(py_attach->obj);
    else if (py_attach) {
        PyErr_SetString(PyExc_TypeError, "attach should be a GtkWidget or None");
        return -1;
    }
    self->obj = (GObject *)notify_notification_new(summary, message, icon, attach);

    if (!self->obj) {
        PyErr_SetString(PyExc_RuntimeError, "could not create NotifyNotification object");
        return -1;
    }
    pygobject_register_wrapper((PyObject *)self);
    return 0;
}

static PyObject *
_wrap_notify_notification_update(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "summary", "message", "icon", NULL };
    char *summary, *message = NULL, *icon = NULL;
    int ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "s|zz:NotifyNotification.update", kwlist, &summary, &message, &icon))
        return NULL;
    ret = notify_notification_update(NOTIFY_NOTIFICATION(self->obj), summary, message, icon);
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_notify_notification_attach_to_widget(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "attach", NULL };
    PyGObject *attach;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O!:NotifyNotification.attach_to_widget", kwlist, &PyGtkWidget_Type, &attach))
        return NULL;
    notify_notification_attach_to_widget(NOTIFY_NOTIFICATION(self->obj), GTK_WIDGET(attach->obj));
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_notify_notification_show(PyGObject *self)
{
    int ret;
    GError *error = NULL;

    ret = notify_notification_show(NOTIFY_NOTIFICATION(self->obj), &error);
    if (pyg_error_check(&error))
        return NULL;
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_notify_notification_set_timeout(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "timeout", NULL };
    int timeout;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:NotifyNotification.set_timeout", kwlist, &timeout))
        return NULL;
    notify_notification_set_timeout(NOTIFY_NOTIFICATION(self->obj), timeout);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_notify_notification_set_category(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "category", NULL };
    char *category;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "s:NotifyNotification.set_category", kwlist, &category))
        return NULL;
    notify_notification_set_category(NOTIFY_NOTIFICATION(self->obj), category);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_notify_notification_set_urgency(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "l", NULL };
    PyObject *py_l = NULL;
    NotifyUrgency l;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O:NotifyNotification.set_urgency", kwlist, &py_l))
        return NULL;
    if (pyg_enum_get_value(NOTIFY_TYPE_URGENCY, py_l, (gint *)&l))
        return NULL;
    notify_notification_set_urgency(NOTIFY_NOTIFICATION(self->obj), l);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_notify_notification_set_icon_from_pixbuf(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "icon", NULL };
    PyGObject *icon;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O!:NotifyNotification.set_icon_from_pixbuf", kwlist, &PyGdkPixbuf_Type, &icon))
        return NULL;
    notify_notification_set_icon_from_pixbuf(NOTIFY_NOTIFICATION(self->obj), GDK_PIXBUF(icon->obj));
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_notify_notification_set_hint_int32(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "key", "value", NULL };
    char *key;
    int value;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "si:NotifyNotification.set_hint_int32", kwlist, &key, &value))
        return NULL;
    notify_notification_set_hint_int32(NOTIFY_NOTIFICATION(self->obj), key, value);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_notify_notification_set_hint_double(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "key", "value", NULL };
    char *key;
    double value;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "sd:NotifyNotification.set_hint_double", kwlist, &key, &value))
        return NULL;
    notify_notification_set_hint_double(NOTIFY_NOTIFICATION(self->obj), key, value);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_notify_notification_set_hint_string(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "key", "value", NULL };
    char *key, *value;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "ss:NotifyNotification.set_hint_string", kwlist, &key, &value))
        return NULL;
    notify_notification_set_hint_string(NOTIFY_NOTIFICATION(self->obj), key, value);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_notify_notification_set_hint_byte(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "key", "value", NULL };
    char *key, value;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "sc:NotifyNotification.set_hint_byte", kwlist, &key, &value))
        return NULL;
    notify_notification_set_hint_byte(NOTIFY_NOTIFICATION(self->obj), key, value);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_notify_notification_set_hint_byte_array(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "key", "value", "len", NULL };
    char *key;
    int value_len;
    guchar *value;
    gsize len;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "ss#k:NotifyNotification.set_hint_byte_array", kwlist, &key, &value, &value_len, &len))
        return NULL;
    notify_notification_set_hint_byte_array(NOTIFY_NOTIFICATION(self->obj), key, value, len);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_notify_notification_clear_hints(PyGObject *self)
{
    notify_notification_clear_hints(NOTIFY_NOTIFICATION(self->obj));
    Py_INCREF(Py_None);
    return Py_None;
}

#line 146 "pynotify.override"
static PyObject *
_wrap_notify_notification_add_action(PyGObject *self, PyObject *args,
									 PyObject *kwargs)
{
    static char *kwlist[] = { "action", "label", "callback",
	                          "user_data", NULL };
	ActionCbData *action_cb_data;
	PyGILState_STATE state;
	PyObject *callback, *user_data = Py_None;
	char *action;
	char *label;
	size_t len;

	state = pyg_gil_state_ensure();

	len = PyTuple_Size(args);

	if (len < 3)
	{
		PyErr_SetString(PyExc_TypeError,
						"NotifyNotification.add_action requires at least "
						"3 arguments");
		return NULL;
	}

	if (!PyArg_ParseTupleAndKeywords(args, kwargs,
									 "ssO|O:NotifyNotification.add_action",
									 kwlist,
									 &action, &label, &callback, &user_data))
	{
		return NULL;
	}

	if (!PyCallable_Check(callback))
	{
		PyErr_SetString(PyExc_TypeError, "third argument must be callable");
		return NULL;
	}

	action_cb_data = g_new0(ActionCbData, 1);
	action_cb_data->callback = callback;
	action_cb_data->user_data = user_data;
	action_cb_data->notification = self;

	Py_INCREF(callback);

	notify_notification_add_action(NOTIFY_NOTIFICATION(self->obj),
								   action, label,
								   NOTIFY_ACTION_CALLBACK(_notify_action_cb),
								   action_cb_data,
								   (GFreeFunc)_action_cb_data_destroy);

	Py_INCREF(Py_None);
	pyg_gil_state_release(state);
	return Py_None;
}
#line 421 "pynotify.c"


static PyObject *
_wrap_notify_notification_clear_actions(PyGObject *self)
{
    notify_notification_clear_actions(NOTIFY_NOTIFICATION(self->obj));
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_notify_notification_close(PyGObject *self)
{
    int ret;
    GError *error = NULL;

    ret = notify_notification_close(NOTIFY_NOTIFICATION(self->obj), &error);
    if (pyg_error_check(&error))
        return NULL;
    return PyBool_FromLong(ret);

}

#line 242 "pynotify.override"
static PyObject *
_wrap_notify_notification_set_hint(PyGObject *self, PyObject *args,
								   PyObject *kwargs)
{
	static char *kwlist[] = { "name", "value", NULL };
	char *name;
	PyObject *value;

	if (!PyArg_ParseTupleAndKeywords(args, kwargs,
									 "sO:NotifyNotification.set_hint",
									 kwlist, &name, &value))
	{
		return NULL;
	}

	if (PyString_Check(value))
	{
		notify_notification_set_hint_string(NOTIFY_NOTIFICATION(self->obj),
											name, PyString_AsString(value));
	}
	else if (PyBool_Check(value))
	{
		notify_notification_set_hint_int32(NOTIFY_NOTIFICATION(self->obj),
										   name,
										   PyObject_IsTrue(value) ? 1 : 0);
	}
	else if (PyInt_Check(value))
	{
		notify_notification_set_hint_int32(NOTIFY_NOTIFICATION(self->obj),
										   name, PyInt_AsLong(value));
	}
	else if (PyLong_Check(value))
	{
		notify_notification_set_hint_int32(NOTIFY_NOTIFICATION(self->obj),
										   name, PyLong_AsLong(value));
	}
	else if (PyFloat_Check(value))
	{
		notify_notification_set_hint_double(NOTIFY_NOTIFICATION(self->obj),
											name, PyFloat_AsDouble(value));
	}
	else
	{
		/* TODO: Display an error */
		return NULL;
	}

	Py_INCREF(Py_None);
	return Py_None;
}
// vim: ft=c
#line 497 "pynotify.c"


static PyMethodDef _PyNotifyNotification_methods[] = {
    { "update", (PyCFunction)_wrap_notify_notification_update, METH_VARARGS|METH_KEYWORDS },
    { "attach_to_widget", (PyCFunction)_wrap_notify_notification_attach_to_widget, METH_VARARGS|METH_KEYWORDS },
    { "show", (PyCFunction)_wrap_notify_notification_show, METH_NOARGS },
    { "set_timeout", (PyCFunction)_wrap_notify_notification_set_timeout, METH_VARARGS|METH_KEYWORDS },
    { "set_category", (PyCFunction)_wrap_notify_notification_set_category, METH_VARARGS|METH_KEYWORDS },
    { "set_urgency", (PyCFunction)_wrap_notify_notification_set_urgency, METH_VARARGS|METH_KEYWORDS },
    { "set_icon_from_pixbuf", (PyCFunction)_wrap_notify_notification_set_icon_from_pixbuf, METH_VARARGS|METH_KEYWORDS },
    { "set_hint_int32", (PyCFunction)_wrap_notify_notification_set_hint_int32, METH_VARARGS|METH_KEYWORDS },
    { "set_hint_double", (PyCFunction)_wrap_notify_notification_set_hint_double, METH_VARARGS|METH_KEYWORDS },
    { "set_hint_string", (PyCFunction)_wrap_notify_notification_set_hint_string, METH_VARARGS|METH_KEYWORDS },
    { "set_hint_byte", (PyCFunction)_wrap_notify_notification_set_hint_byte, METH_VARARGS|METH_KEYWORDS },
    { "set_hint_byte_array", (PyCFunction)_wrap_notify_notification_set_hint_byte_array, METH_VARARGS|METH_KEYWORDS },
    { "clear_hints", (PyCFunction)_wrap_notify_notification_clear_hints, METH_NOARGS },
    { "add_action", (PyCFunction)_wrap_notify_notification_add_action, METH_VARARGS|METH_KEYWORDS },
    { "clear_actions", (PyCFunction)_wrap_notify_notification_clear_actions, METH_NOARGS },
    { "close", (PyCFunction)_wrap_notify_notification_close, METH_NOARGS },
    { "set_hint", (PyCFunction)_wrap_notify_notification_set_hint, METH_VARARGS|METH_KEYWORDS },
    { NULL, NULL, 0 }
};

PyTypeObject PyNotifyNotification_Type = {
    PyObject_HEAD_INIT(NULL)
    0,					/* ob_size */
    "pynotify.Notification",			/* tp_name */
    sizeof(PyGObject),	        /* tp_basicsize */
    0,					/* tp_itemsize */
    /* methods */
    (destructor)0,	/* tp_dealloc */
    (printfunc)0,			/* tp_print */
    (getattrfunc)0,	/* tp_getattr */
    (setattrfunc)0,	/* tp_setattr */
    (cmpfunc)0,		/* tp_compare */
    (reprfunc)0,		/* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,		/* tp_hash */
    (ternaryfunc)0,		/* tp_call */
    (reprfunc)0,		/* tp_str */
    (getattrofunc)0,	/* tp_getattro */
    (setattrofunc)0,	/* tp_setattro */
    (PyBufferProcs*)0,	/* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,                      /* tp_flags */
    NULL, 				/* Documentation string */
    (traverseproc)0,	/* tp_traverse */
    (inquiry)0,		/* tp_clear */
    (richcmpfunc)0,	/* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,		/* tp_iter */
    (iternextfunc)0,	/* tp_iternext */
    _PyNotifyNotification_methods,			/* tp_methods */
    0,					/* tp_members */
    0,		       	/* tp_getset */
    NULL,				/* tp_base */
    NULL,				/* tp_dict */
    (descrgetfunc)0,	/* tp_descr_get */
    (descrsetfunc)0,	/* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)_wrap_notify_notification_new,		/* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0              /* tp_is_gc */
};



/* ----------- functions ----------- */

static PyObject *
_wrap_notify_init(PyObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "app_name", NULL };
    char *app_name;
    int ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "s:init", kwlist, &app_name))
        return NULL;
    ret = notify_init(app_name);
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_notify_uninit(PyObject *self)
{
    notify_uninit();
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_notify_is_initted(PyObject *self)
{
    int ret;

    ret = notify_is_initted();
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_notify_get_app_name(PyObject *self)
{
    const gchar *ret;

    ret = notify_get_app_name();
    if (ret)
        return PyString_FromString(ret);
    Py_INCREF(Py_None);
    return Py_None;
}

#line 204 "pynotify.override"
static PyObject *
_wrap_notify_get_server_caps(PyObject *self)
{
	return pygalago_wrap_str_list(notify_get_server_caps());
}
#line 620 "pynotify.c"


#line 211 "pynotify.override"
static PyObject *
_wrap_notify_get_server_info(PyObject *self)
{
	char *name;
	char *vendor;
	char *version;
	char *spec_version;
	PyObject *dict;

	if (!notify_get_server_info(&name, &vendor, &version, &spec_version))
	{
		Py_INCREF(Py_None);
		return Py_None;
	}

	dict = PyDict_New();
	PyDict_SetItemString(dict, "name", PyString_FromString(name));
	PyDict_SetItemString(dict, "vendor", PyString_FromString(vendor));
	PyDict_SetItemString(dict, "version", PyString_FromString(version));
	PyDict_SetItemString(dict, "spec-version",
						 PyString_FromString(spec_version));

	g_free(name);
	g_free(vendor);
	g_free(version);
	g_free(spec_version);

	return dict;
}
#line 653 "pynotify.c"


PyMethodDef pypynotify_functions[] = {
    { "init", (PyCFunction)_wrap_notify_init, METH_VARARGS|METH_KEYWORDS },
    { "uninit", (PyCFunction)_wrap_notify_uninit, METH_NOARGS },
    { "is_initted", (PyCFunction)_wrap_notify_is_initted, METH_NOARGS },
    { "get_app_name", (PyCFunction)_wrap_notify_get_app_name, METH_NOARGS },
    { "get_server_caps", (PyCFunction)_wrap_notify_get_server_caps, METH_VARARGS },
    { "get_server_info", (PyCFunction)_wrap_notify_get_server_info, METH_VARARGS },
    { NULL, NULL, 0 }
};


/* ----------- enums and flags ----------- */

void
pypynotify_add_constants(PyObject *module, const gchar *strip_prefix)
{
  pyg_enum_add(module, "Urgency", strip_prefix, NOTIFY_TYPE_URGENCY);

  if (PyErr_Occurred())
    PyErr_Print();
}

/* initialise stuff extension classes */
void
pypynotify_register_classes(PyObject *d)
{
    PyObject *module;

    if ((module = PyImport_ImportModule("gobject")) != NULL) {
        PyObject *moddict = PyModule_GetDict(module);

        _PyGObject_Type = (PyTypeObject *)PyDict_GetItemString(moddict, "GObject");
        if (_PyGObject_Type == NULL) {
            PyErr_SetString(PyExc_ImportError,
                "cannot import name GObject from gobject");
            return;
        }
    } else {
        PyErr_SetString(PyExc_ImportError,
            "could not import gobject");
        return;
    }
    if ((module = PyImport_ImportModule("gtk")) != NULL) {
        PyObject *moddict = PyModule_GetDict(module);

        _PyGtkWidget_Type = (PyTypeObject *)PyDict_GetItemString(moddict, "Widget");
        if (_PyGtkWidget_Type == NULL) {
            PyErr_SetString(PyExc_ImportError,
                "cannot import name Widget from gtk");
            return;
        }
        _PyGtkStatusIcon_Type = (PyTypeObject *)PyDict_GetItemString(moddict, "StatusIcon");
        if (_PyGtkStatusIcon_Type == NULL) {
            PyErr_SetString(PyExc_ImportError,
                "cannot import name StatusIcon from gtk");
            return;
        }
    } else {
        PyErr_SetString(PyExc_ImportError,
            "could not import gtk");
        return;
    }
    if ((module = PyImport_ImportModule("gtk.gdk")) != NULL) {
        PyObject *moddict = PyModule_GetDict(module);

        _PyGdkPixbuf_Type = (PyTypeObject *)PyDict_GetItemString(moddict, "Pixbuf");
        if (_PyGdkPixbuf_Type == NULL) {
            PyErr_SetString(PyExc_ImportError,
                "cannot import name Pixbuf from gtk.gdk");
            return;
        }
    } else {
        PyErr_SetString(PyExc_ImportError,
            "could not import gtk.gdk");
        return;
    }


#line 734 "pynotify.c"
    pygobject_register_class(d, "NotifyNotification", NOTIFY_TYPE_NOTIFICATION, &PyNotifyNotification_Type, Py_BuildValue("(O)", &PyGObject_Type));
}
