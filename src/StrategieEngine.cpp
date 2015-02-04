#include <StrategieEngine.h>
#include <GameRoot.h>
#include <RobotCommand.h>
#include <PythonVisionFrame.h>
using namespace boost::python;
using namespace boost::python::api;

StrategieEngine::StrategieEngine(){
   this->initPythonInterpreter();
}

void StrategieEngine::initPythonInterpreter() {
    Py_Initialize();
    PyEval_InitThreads();

    PyObject *sys = PyImport_ImportModule("sys");
    PyObject *path = PyObject_GetAttrString(sys, "path");
    PyList_Append(path, PyUnicode_FromString("./scripts"));
    PyList_Append(path, PyUnicode_FromString("./Python"));
    PyList_Append(path, PyUnicode_FromString("."));

    PyEval_ReleaseLock();
}

void StrategieEngine::launch() {
    this->updateThread = std::thread(&StrategieEngine::updatePosition, this);
}

StrategieEngine::~StrategieEngine(){
	this->terminate();
}

void StrategieEngine::updatePosition(){
	PyGILState_STATE gstate;
	gstate = PyGILState_Ensure(); //Le thread aquérit l'interpreteur Python

	object pModule, pFunc;
	
	pModule = import("main");

	if (pModule != NULL) {
		pFunc = pModule.attr("update");

		if (pFunc) {
			//Boucle principale du thread 
			while(!this->threadTerminated){
				pFunc(); //Call Python function
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
			}

		}
		else {
		    if (PyErr_Occurred())
			PyErr_Print();
		    fprintf(stderr, "Cannot find function");
		}
		
	}
	else {
		PyErr_Print();
		fprintf(stderr, "Failed to load ");
	}

	PyGILState_Release (gstate); 

}


void StrategieEngine::terminate() {
    this->threadTerminated = true;
    if(this->updateThread.joinable())
        this->updateThread.join();
    Py_Finalize();
}

void StrategieEngine::visionFrameRetrieved(std::queue<std::shared_ptr<Rule::VisionFrame>> visionFrames) {

}

void StrategieEngine::refereeCommandRetrieved(std::queue<std::shared_ptr<Rule::RefereeCommand>> refereeCommand) {

}

template<class T>
list StrategieEngine::vectorToPython(const std::vector<T>& v)
{
    list plist;
    for (auto &element : v){
        plist.append(element);
    }
    return plist;
};
