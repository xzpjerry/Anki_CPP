#include <iostream>
#include <python2.7/Python.h>

using namespace std;

int main(int argc, char *argv[])
{
    Py_Initialize();

    string path = "./";
    string chdir_cmd = string("sys.path.append(\"") + path + "\")";
    const char* cstr_cmd = chdir_cmd.c_str();

    PyRun_SimpleString("print 'hello'");
    PyRun_SimpleString("import sys");
    PyRun_SimpleString(cstr_cmd);

    PyObject* moduleName = PyString_FromString("py_functions");
	PyObject* pModule = PyImport_Import(moduleName);
	if (!pModule) // if fails
    {
        cout << "[ERROR] Python get module failed." << endl;
        return 0;
    }
    cout << "[INFO] Python get module succeed." << endl;

    PyObject* pv = PyObject_GetAttrString(pModule, "multiply");
    if (!pv || !PyCallable_Check(pv))  // if the function is not exisited
    {
        cout << "[ERROR] Can't find funftion (multiply)" << endl;
        return 0;
    }
    cout << "[INFO] Get function (multiply) succeed." << endl;

    PyObject* args = PyTuple_New(2);   // build a python tuple with size 2
    PyObject* arg1 = PyInt_FromLong(4);    // 1st argument is 4
    PyObject* arg2 = PyInt_FromLong(3);    // 2nd arugment is 3
    PyTuple_SetItem(args, 0, arg1); // set the tuple[0] as 4
    PyTuple_SetItem(args, 1, arg2); // set the tuple[1] as 3

    PyObject* pRet = PyObject_CallObject(pv, args); // call python script

    if (pRet)  // check result
    {
        long result = PyInt_AsLong(pRet);
        cout << "result:" << result << endl;
    }
    

    Py_Finalize();
    return 0;
}