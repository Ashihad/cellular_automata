#include "AutomataViews.hpp"
#include "AutomataModels.hpp"

#include <iostream>

Automata1DFileWriter::Automata1DFileWriter(std::shared_ptr<Automata1DModel> ptr, const std::string filename):
    writeStream {filename}
    {
        model_ptr.reset();
        model_ptr = std::weak_ptr<Automata1DModel> {ptr};
    }

void Automata1DFileWriter::writeBoard() {
    const Board1DType& board {std::shared_ptr<Automata1DModel>{model_ptr.lock()}->getBoard()}; 
    const char aliveModelSymbol { std::shared_ptr<Automata1DModel>{model_ptr.lock()}->aliveInternal };
    for (auto iter = cbegin(board); iter != cend(board); ++iter) {
        writeStream << ((*iter == aliveModelSymbol) ? aliveSymbol : deadSymbol) << ' ';
    }
    writeStream << '\n';
}