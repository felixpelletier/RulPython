#include <StrategieEngine.h>
#include <sys/time.h>

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
   
    this->updateThread = boost::thread(&StrategieEngine::updatePosition, this);//Démarrage du thread
}

StrategieEngine::~StrategieEngine(){
	this->updateThread.interrupt();
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

			//Boucle principale du thread (infinie pour l'instant)
			while(1){

				pFunc(); //Call Python function

				boost::this_thread::interruption_point();//This is where the thread stops if it gets interrupted

				boost::this_thread::sleep(boost::posix_time::milliseconds(50));
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

