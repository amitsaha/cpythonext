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


static PyObject *square_square(PyObject *self, PyObject *args)
{
    int x;

    /* Parse the input tuple 
    * https://docs.python.org/2/c-api/arg.html#c.PyArg_ParseTuple
    */
    if (!PyArg_ParseTuple(args, "i", &x))
        return NULL;
  
    int squared = square(x);
    
    PyObject *ret = Py_BuildValue("i", squared);

    return ret;

}


