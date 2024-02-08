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
        *iter = deadInternal;

    *iter = aliveInternal;
    iter++;

    for (; iter != end(board); ++iter)
        *iter = deadInternal;
}

void Automata1DModel::nextState() {
    // reset tmpBoard
    std::fill(begin(tmpBoard), end(tmpBoard), deadInternal);
    
    // apply rule
    auto tmpBoardIt { begin(tmpBoard) };
    auto boardIt { begin(board) };
    for (; tmpBoardIt != end(tmpBoard); ++tmpBoardIt, ++boardIt) {
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
    rule = [binary_rule, aliveInternal=aliveInternal] (char left, char middle, char right) {
        // convert alive/dead statuses to access binary_rule string by index
        size_t index {  static_cast<size_t> (
                        7 - (left == aliveInternal ? 4 : 0)
                        - (middle == aliveInternal ? 2 : 0)
                        - (right == aliveInternal ? 1 : 0) 
                        ) };
        if (index <= 7) return binary_rule[index];
        // if function does not exit by now something went wrong
        throw std::logic_error("Rule broken");
    };
}