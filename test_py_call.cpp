#define PY_SSIZE_T_CLEAN
#include <Python.h>

int main() {
    Py_Initialize();
    PyRun_SimpleString("import sys");
    PyRun_SimpleString('sys.path.append("encode.py")')
}