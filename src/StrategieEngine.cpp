#include <StrategieEngine.h>
#include <GameRoot.h>
#include <RobotCommand.h>
#include <PythonVisionFrame.h>
#include <PythonRefereeCommand.h>
#include <iostream>
using namespace boost::python;
using namespace boost::python::api;

StrategieEngine::StrategieEngine(int buffersLength)
        : visionFrames(buffersLength), refereeCommands(buffersLength) {
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
	
	try{
		pModule = import("main");
		pFunc = pModule.attr("update");
	}
	catch(boost::python::error_already_set){
		PyErr_Print();	
		throw;
	}

	//Boucle principale du thread 
	while(!this->threadTerminated){
		try{
			list py_frames = dumpVisionBuffer(visionFrames);
			list py_refereeCommands = dumpRefereeBuffer(refereeCommands);
			pFunc(py_frames, py_refereeCommands);//Call Python function
		}
		catch(boost::python::error_already_set){
			PyErr_Print();	
			throw;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
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
    while(!newRefereeCommand.empty()){
        std::shared_ptr<Rule::RefereeCommand> refereePtr;
        refereePtr = newRefereeCommand.back();
        this->refereeCommands.push_front(refereePtr);
        newRefereeCommand.pop();
    }
}

list StrategieEngine::dumpVisionBuffer(Streams::ThreadSafeCircularBuffer<std::shared_ptr<Rule::VisionFrame>>& buffer){
    boost::python::list plist;
    int size = buffer.getSize();
    for (int i = 0; i < size; i++){
	std::shared_ptr<Rule::VisionFrame> element;
	buffer.pop_back(&element);
	Rule::PythonVisionFrame pyelement = Rule::PythonVisionFrame(*element); 
	plist.append(pyelement);
    }
    return plist;
}

list StrategieEngine::dumpRefereeBuffer(Streams::ThreadSafeCircularBuffer<std::shared_ptr<Rule::RefereeCommand>>& buffer){
    boost::python::list plist;
    int size = buffer.getSize();
    for (int i = 0; i < size; i++){
	std::shared_ptr<Rule::RefereeCommand> element;
	buffer.pop_back(&element);
	Rule::PythonRefereeCommand pyelement = Rule::PythonRefereeCommand(*element); 
	plist.append(pyelement);
    }
    return plist;
}
