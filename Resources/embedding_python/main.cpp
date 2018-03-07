#include <iostream>
#include <python2.7/Python.h>

using namespace std;

int main(int argc, char *argv[])
{
    Py_Initialize();

    string path = "./";
    string chdir_cmd = string("sys.path.append(\"") + path + "\")";
    const char* cstr_cmd = chdir_cmd.c_str();
    cout << cstr_cmd << endl;

    PyRun_SimpleString("print 'hello'");
    PyRun_SimpleString("import sys");
    PyRun_SimpleString(cstr_cmd);

    // import targeted module
    PyObject* moduleName = PyString_FromString("dbtrial");
	PyObject* pModule = PyImport_Import(moduleName);
	if (!pModule) // if fails
    {
        cout << "[ERROR] Python get module failed." << endl;
        return 0;
    }
    cout << "[INFO] Python get module succeed." << endl;

    PyObject* pv = PyObject_GetAttrString(pModule, "test");
    if (!pv || !PyCallable_Check(pv))  // if the function is not exisited
    {
        cout << "[ERROR] Can't find funftion (test)" << endl;
        return 0;
    }
    cout << "[INFO] Get function (test) succeed." << endl;

    PyObject* args = PyTuple_New(2);   // build a python tuple with size 2
    PyObject* arg1 = Py_BuildValue("s", "hello");    // 1st argument is "hello"
    PyObject* arg2 = Py_BuildValue("s", "world");    // 2nd arugment is "world"
    PyTuple_SetItem(args, 0, arg1); // set the tuple[0] as 4
    PyTuple_SetItem(args, 1, arg2); // set the tuple[1] as 3

    PyObject* pRet = PyObject_CallObject(pv, args); // call python script

    if (pRet)  // check result
    {
        string result = PyString_AsString(pRet);
        cout << "result:" << result << endl;
    }
    

    Py_Finalize();
    return 0;
}