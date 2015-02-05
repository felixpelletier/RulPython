#include <StrategieEngine.h>
#include <chrono>
#include <iostream>
#include <GameRoot.h>
#include <RobotCommand.h>
#include <PythonVisionFrame.h>
using namespace boost::python;
using namespace boost::python::api;

StrategieEngine::StrategieEngine(){

    Py_Initialize();
    PyEval_InitThreads();
    
    //Ajouter le dossier 'scripts' au path temporaire Python
    PyObject *sys = PyImport_ImportModule("sys");
    PyObject *path = PyObject_GetAttrString(sys, "path");
    PyList_Append(path, PyUnicode_FromString("./scripts"));
    PyList_Append(path, PyUnicode_FromString("./Python"));
    PyList_Append(path, PyUnicode_FromString("."));

    //Relacher l'exclusivité de l'interpreteur
    //pour pouvoir l'utiliser sur les autres threads
    PyEval_ReleaseLock(); 
   
    this->updateThread = std::thread(&StrategieEngine::updatePosition, this);//Démarrage du thread
}

StrategieEngine::~StrategieEngine(){
	this->threadTerminated = true;
	this->updateThread.join();
	Py_Finalize();	
}

//Le thread démarre sur cette fonction
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
					pFunc();//Call Python function
				}
				catch(boost::python::error_already_set){
					PyErr_Print();	
					throw;
				}
                		std::this_thread::sleep_for(std::chrono::milliseconds(2));
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

template<class T>
list vectorToPython(const std::vector<T>& v)
{
    list plist;
    for (auto &element : v){
        plist.append(element);
    }
    return plist;
};
