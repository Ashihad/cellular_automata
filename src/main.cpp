#include "AutomataControllers.hpp"

#include <iostream>

int main() {
    AutomataController test_automata;
    test_automata.setModel(Model::Square2D, 9, 90);
    test_automata.setView(ViewMode::Printmode2D);
    // test_automata.setView(ViewMode::Filemode);
    test_automata.runModel(4);
    return 0;
}