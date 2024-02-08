#include "AutomataControllers.hpp"

#include <iostream>

int main() {
    AutomataController test_automata;
    test_automata.setModel(Model::Basic1D, 31, 90);
    test_automata.setView(ViewMode::Printmode);
    test_automata.runModel(15);
    return 0;
}