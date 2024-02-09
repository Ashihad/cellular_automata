#include "AutomataModels.hpp"

#include <cassert>

Automata2DSquareModel::Automata2DSquareModel(const std::size_t size):
    Automata2DSquareModel::Automata2DSquareModel(size, size) {}

Automata2DSquareModel::Automata2DSquareModel(const std::size_t x_size, const std::size_t y_size) {
    // create boards
    board.resize(x_size);
    for (auto& row : board) {
        row.resize(y_size);
    }
    tmpBoard.resize(x_size);
    for (auto& row : tmpBoard) {
        row.resize(y_size);
    }
    // default is Moore neighborghood
    neighborhood.resize(9);

    // default board is three alive cells in a row, one row below start
    assert(x_size >= 2 && y_size >= 3);
    for (auto rowIter = begin(board); rowIter != end(board); ++rowIter) {
        for (auto collIter = begin(*rowIter); collIter != end(*rowIter); ++collIter) {
            *collIter = deadInternal;
        }
    }
    auto rowIterBegin {std::next(begin(board), 1)};
    auto rowIterEnd {std::next(begin(board), 2)};
    auto collIterBegin {*rowIterBegin};
    auto collIterEnd {std::next(*rowIterBegin, 4)};
    for (auto rowIter = rowIterBegin; rowIter != rowIterEnd; ++rowIter) {
        for (auto collIter = collIterBegin; collIter != collIterEnd; ++collIter) {
            *collIter = aliveInternal;
        }
    }

}

void Automata2DSquareModel::nextState() {
    return;
}

void Automata2DSquareModel::setRule(const uint8_t) {
    rule = [aliveInternal=aliveInternal] (std::vector<char>& neighborhood) {
        // convert alive/dead statuses to access binary_rule string by index
        int alive { std::count(begin(neighborhood), end(neighborhood), aliveInternal) }
        if (index <= 7) return binary_rule[index];
        // if function does not exit by now something went wrong
        throw std::logic_error("Rule broken");
    };
    return;
}