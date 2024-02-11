#include "AutomataControllers.hpp"

#include <iostream>

int main() {
    AutomataController test_automata(Model::Square2D, 9, ViewMode::Printmode);
    test_automata.runModel(4);
    return 0;
}