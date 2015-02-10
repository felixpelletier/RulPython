#include "PythonApplication.h"
#include <RuleException.h>
#include <iostream>
#include <csignal>

PythonApplication app;
void appterminate(int sig);

int main() {
    signal(SIGINT, &appterminate);
    try {
        app.run();
    } catch(Rule::RuleException &e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}

void appterminate(int sig){
    app.terminate();
}
