#include "PythonApplication.h"
#include <RuleException.h>
#include <iostream>

int main() {
    PythonApplication app;

    try {
        app.run();
    } catch(Rule::RuleException &e) {
        std::cout << e.what() << std::endl;
        return 1;
    }

    return 0;
}
