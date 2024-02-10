#include "AutomataViews.hpp"
#include "AutomataModels.hpp"

#include <iostream>

Automata2DSquareConsoleWriter::Automata2DSquareConsoleWriter(std::shared_ptr<Automata2DSquareModel> ptr) {
    model_ptr.reset();
    model_ptr = std::weak_ptr<Automata2DSquareModel> {ptr};
}

void Automata2DSquareConsoleWriter::writeBoard() {
    const Board2DType& board { std::shared_ptr<Automata2DSquareModel>{model_ptr.lock()}->getBoard() }; 
    const char aliveModelSymbol { std::shared_ptr<Automata2DSquareModel>{model_ptr.lock()}->aliveInternal };
    for (auto iterRow = cbegin(board); iterRow != cend(board); ++iterRow) {
        for (auto iterColl = iterRow->begin(); iterColl != iterRow->end(); ++iterColl) {
            std::cout << ((*iterColl == aliveModelSymbol) ? aliveSymbol : deadSymbol) << ' ';
        }
        std::cout << '\n';
    }
    std::cout << std::endl << std::endl;
}


std::string Automata2DSquareConsoleWriter::getTag() {
    return tag;
}