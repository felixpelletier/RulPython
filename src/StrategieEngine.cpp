#include <StrategieEngine.h>
#include <GameRoot.h>
#include <RobotCommand.h>
#include <PythonVisionFrame.h>
using namespace boost::python;
using namespace boost::python::api;

StrategieEngine::StrategieEngine(int buffersLenght)
        : visionFrames(buffersLenght) {
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
				try{
					std::cout << "calling Python" << std::endl;
                			std::cout << this->visionFrames.getSize() << std::endl;
					pFunc();//Call Python function
				}
				catch(boost::python::error_already_set){
					PyErr_Print();	
					throw;
				}
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

void StrategieEngine::visionFrameRetrieved(std::queue<std::shared_ptr<Rule::VisionFrame>> newVisionFrames) {
    while(!newVisionFrames.empty()){
        std::shared_ptr<Rule::VisionFrame> framePtr;
        framePtr = newVisionFrames.back();
        this->visionFrames.push_front(framePtr);
        newVisionFrames.pop();
    }
}

void StrategieEngine::refereeCommandRetrieved(std::queue<std::shared_ptr<Rule::RefereeCommand>> newRefereeCommand) {
    std::cout << "Receive a ref" << std::endl;
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
