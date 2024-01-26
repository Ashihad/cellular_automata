#include "AutomataModels.hpp"
#include "AutomataControllers.hpp"

#include <iostream>
#include <algorithm>
#include <exception>

Automata1DModel::Automata1DModel(std::size_t newSize) {
    // create board
    board.resize(newSize);
    std::fill(board.begin(), board.end(), 0);
}

void Automata1DModel::nextState() {
    Board1DType newBoard;
    newBoard.resize(board.size());
    std::fill(begin(newBoard), end(newBoard), '0');
    for (size_t i = 1; i < newBoard.size()-1; ++i) {
        if (board[i-1] == '1' && board[i+1] == '1') newBoard[i] = '1';    // rule 161
    }
}