#include "AutomataModels.hpp"
#include "AutomataControllers.hpp"

#include <iostream>
#include <algorithm>
#include <exception>
#include <bitset>

Automata1DModel::Automata1DModel(const std::size_t newSize) {
    // create board
    board.resize(newSize);
    tmpBoard.resize(newSize);

    // default board is standard Wikipedia test one, middle cell is alive, rest is dead
    for (size_t i = 0; i < newSize/2; ++i) {
        board[i] = '0';
    }
    board[newSize/2] = '1';
    for (size_t i = newSize/2+1; i < newSize; ++i) {
        board[i] = '0';
    }
}

void Automata1DModel::nextState() {
    // reset tmpBoard
    std::fill(begin(tmpBoard), end(tmpBoard), '0');
    for (size_t i = 0; i < tmpBoard.size(); ++i) {
        // index wraps around in case of out of bounds access
        // (i + newBoard.size() - 1) prevents overflow, since i is of type size_t
        tmpBoard[i] = rule(board[(i + tmpBoard.size() - 1) % tmpBoard.size()], board[i], board[(i + 1) % tmpBoard.size()]);
    }
    // commit to next state
    std::swap(board, tmpBoard);
}

void Automata1DModel::setRule(const uint8_t rule_no) {
    // convert unsigned 8 bit int to bits and then to string, for ease of iteration
    std::string binary_rule { std::bitset<8>(rule_no).to_string() };

    // construct automata rule from bits
    // see  https://en.wikipedia.org/wiki/Elementary_cellular_automaton
    rule = [binary_rule] (char left, char middle, char right) {
        if (left == '1' && middle == '1' && right == '1') return binary_rule[0];
        else if (left == '1' && middle == '1' && right == '0') return binary_rule[1];
        else if (left == '1' && middle == '0' && right == '1') return binary_rule[2];
        else if (left == '1' && middle == '0' && right == '0') return binary_rule[3];
        else if (left == '0' && middle == '1' && right == '1') return binary_rule[4];
        else if (left == '0' && middle == '1' && right == '0') return binary_rule[5];
        else if (left == '0' && middle == '0' && right == '1') return binary_rule[6];
        else if (left == '0' && middle == '0' && right == '0') return binary_rule[7];
        // if function does not exit by now something went wrong
        throw std::logic_error("Rule broken");
    };
}