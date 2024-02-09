#include "AutomataViews.hpp"
#include "AutomataModels.hpp"

#include <iostream>

Automata1DConsoleWriter::Automata1DConsoleWriter(std::shared_ptr<Automata1DModel> ptr) {
    model_ptr.reset();
    model_ptr = std::weak_ptr<Automata1DModel> {ptr};
}

void Automata1DConsoleWriter::writeBoard() {
    const Board1DType& board { std::shared_ptr<Automata1DModel>{model_ptr.lock()}->getBoard() }; 
    const char aliveModelSymbol { std::shared_ptr<Automata1DModel>{model_ptr.lock()}->aliveInternal };
    for (auto iter = cbegin(board); iter != cend(board); ++iter) {
        std::cout << ((*iter == aliveModelSymbol) ? aliveSymbol : deadSymbol) << ' ';
    }
    std::cout << '\n';
}

std::string Automata1DConsoleWriter::getTag() {
    return tag;
}