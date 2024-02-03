#include "AutomataModels.hpp"
#include "AutomataControllers.hpp"

#include <iostream>
#include <algorithm>
#include <exception>
#include <bitset>

Automata1DModel::Automata1DModel(std::size_t newSize) {
    // create board
    board.resize(newSize);
    srand(time(NULL));
    for (size_t i = 0; i < 15; ++i) {
        board[i] = '0';
    }
    board[15] = '1';
    for (size_t i = 16; i < 31; ++i) {
        board[i] = '0';
    }
    // for (auto iter = begin(board); iter != end(board); ++iter) {
    //     *iter = rand() % 2 ? '0' : '1';
    // }
}

void Automata1DModel::nextState() {
    Board1DType newBoard;
    newBoard.resize(board.size());
    std::fill(begin(newBoard), end(newBoard), '0');
    for (size_t i = 1; i < newBoard.size()-1; ++i) {
        // if (board[i-1] == '1' && board[i+1] == '1') newBoard[i] = '1';    // rule 161
        newBoard[i] = rule(board[i-1], board[i], board[i+1]);
    }
    board = newBoard;
}

void Automata1DModel::setRule(const uint8_t rule_no) {
    std::string binary_rule { std::bitset<8>(rule_no).to_string() };

    rule = [binary_rule] (char left, char middle, char right) {
        if (left == '1' && middle == '1' && right == '1') return binary_rule[0];
        else if (left == '1' && middle == '1' && right == '0') return binary_rule[1];
        else if (left == '1' && middle == '0' && right == '1') return binary_rule[2];
        else if (left == '1' && middle == '0' && right == '0') return binary_rule[3];
        else if (left == '0' && middle == '1' && right == '1') return binary_rule[4];
        else if (left == '0' && middle == '1' && right == '0') return binary_rule[5];
        else if (left == '0' && middle == '0' && right == '1') return binary_rule[6];
        else if (left == '0' && middle == '0' && right == '0') return binary_rule[7];
        throw std::logic_error("Rule broken");
    };
}