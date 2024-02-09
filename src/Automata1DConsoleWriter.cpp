#include "AutomataViews.hpp"
#include "AutomataModels.hpp"

#include <iostream>

Automata1DConsoleWriter::Automata1DConsoleWriter(std::shared_ptr<Automata1DModel> ptr) {
    model_ptr.reset();
    model_ptr = std::weak_ptr<Automata1DModel> {ptr};
}

void Automata1DConsoleWriter::writeBoard() {
    const Board1DType& board {std::shared_ptr<Automata1DModel>{model_ptr.lock()}->getBoard()}; 
    for (auto iter = cbegin(board); iter != cend(board); ++iter) {
        std::cout << ((*iter == '1') ? aliveSymbol : deadSymbol) << ' ';
    }
    std::cout << '\n';
}