#include "AutomataModels.hpp"
#include "AutomataControllers.hpp"

#include <iostream>
#include <algorithm>
#include <exception>
#include <bitset>

Automata1DModel::Automata1DModel(const std::size_t newSize) {
    // create boards
    board.resize(newSize);
    tmpBoard.resize(newSize);

    // default board is standard Wikipedia test one, middle cell is alive, rest is dead
    auto iter { begin(board) };
    auto middle { begin(board) };
    std::advance(middle, newSize/2);

    for (; iter != middle; ++iter)
        *iter = '0';

    *iter = '1';
    iter++;

    for (; iter != end(board); ++iter)
        *iter = '0';
}

void Automata1DModel::nextState() {
    // reset tmpBoard
    std::fill(begin(tmpBoard), end(tmpBoard), '0');
    
    auto tmpBoardIt { begin(tmpBoard) };
    auto boardIt { begin(board) };
    for (; tmpBoardIt != end(tmpBoard); ++tmpBoardIt, ++boardIt) {
        // index wraps around in case of out of bounds access
        // wrap around if there is out of bound access
        // in case of one-before-first return last
        // in case of one-after-last return first
        *tmpBoardIt = rule( boardIt != begin(board) ? *std::prev(boardIt) : *std::prev(end(board)), 
                            *boardIt, 
                            std::next(boardIt) != end(board) ? *std::next(boardIt) : *begin(board));
    }
    // commit next state
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