#include <Python.h>
#include "square.h"

static char module_docstring[] =
    "This module exports a C function square().";
static char square_docstring[] =
    "Calculate the square of an integer.";

static PyObject *square_square(PyObject *self, PyObject *args);

static PyMethodDef module_methods[] = {
    {"square", square_square, METH_VARARGS, square_docstring},
    {NULL, NULL, 0, NULL}
};

PyMODINIT_FUNC init_square(void)
{
    PyObject *m = Py_InitModule3("_square", module_methods, module_docstring);
    if (m == NULL)
        return;
}


static PyObject *chi2_chi2(PyObject *self, PyObject *args)
{
    int x;
    PyObject *x_obj;

    /* Parse the input tuple */
    if (!PyArg_ParseTuple(args, "d", &x, &x_obj))
        return NULL;


}


