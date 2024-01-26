#include "AutomataControllers.hpp"

#include <iostream>

int main() {
    AutomataController test_automata;
    test_automata.setModel(Model::Basic1D);
    test_automata.setView(ViewMode::Printmode);
    test_automata.runModel(10);
    return 0;
}