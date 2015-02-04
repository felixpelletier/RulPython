#include "PythonApplication.h"

#include <GameRoot.h>


void PythonApplication::createGame() {
    this->strategie.launch();
}


void PythonApplication::createListeners() {
    Rule::GameRoot::getSingleton().addRefereeListener(&this->strategie);
    Rule::GameRoot::getSingleton().addRefereeListener(&this->strategie);
}

