#include "AutomataViews.hpp"
#include "AutomataModels.hpp"

#include <iostream>

void Automata1DConsoleWriter::writeBoard() const {
    const Board1DType& board {std::shared_ptr<Automata1DModel>{model_ptr.lock()}->getBoard()}; 
    for (auto iter = cbegin(board); iter != cend(board); ++iter) {
        std::cout << *iter << ' ';
    }
    std::cout << '\n';
}