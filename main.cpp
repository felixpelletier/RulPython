#include "ExampleApplication.h"
#include <RuleException.h>
#include <iostream>

int main() {
    ExampleApplication app;

    try {
        app.run();
    } catch(Rule::RuleException &e) {
        std::cout << e.what() << std::endl;
        return 1;
    }

    return 0;
}
