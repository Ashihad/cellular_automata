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

    // default board is three alive cells in a row, one row below start, so called oscillator
    setOscillator();

    setRule(Rule2D::Conway);

}

void Automata2DSquareModel::nextState() {
    // reset tmpBoard
    for (auto& row : tmpBoard)
        std::fill(begin(row), end(row), deadInternal);

    auto iterRow = std::next(begin(board));
    auto tmpIterRow = std::next(begin(tmpBoard));
    for (; iterRow != std::prev(end(board)); ++iterRow, ++tmpIterRow) {
        auto iterColl = std::next(iterRow->begin());
        auto tmpIterColl = std::next(tmpIterRow->begin());
        for (; iterColl != std::prev(iterRow->end()); ++iterColl, ++tmpIterColl) {
            // construct neighborhood
            auto distance { std::distance(iterRow->begin(), iterColl) };

            auto previousRow { std::prev(iterRow) };
            neighborhood[0] = *std::next(previousRow->begin(), distance-1);
            neighborhood[1] = *std::next(previousRow->begin(), distance);
            neighborhood[2] = *std::next(previousRow->begin(), distance+1);
            
            neighborhood[3] = *std::prev(iterColl);
            neighborhood[4] = *iterColl;
            neighborhood[5] = *std::next(iterColl);
            
            auto nextRow { std::next(iterRow) };
            neighborhood[6] = *std::next(nextRow->begin(), distance-1);
            neighborhood[7] = *std::next(nextRow->begin(), distance);
            neighborhood[8] = *std::next(nextRow->begin(), distance+1);
            
            *tmpIterColl = rule(neighborhood);
        }
    }
    std::swap(board, tmpBoard);
}

void Automata2DSquareModel::setRule(Rule2D ruleEnum) {
    switch (ruleEnum) {
        case Rule2D::Conway:
            // classic conways game of life rule
            rule = [alive=aliveInternal, dead=deadInternal] (std::vector<char>& neighborhood) {
                // convert alive/dead statuses to access binary_rule string by index
                long int aliveNeighbors { std::count(begin(neighborhood), std::next(begin(neighborhood), 5), alive)
                                        + std::count(std::next(begin(neighborhood), 6), end(neighborhood), alive) };
                bool isAlive { *std::next(begin(neighborhood), 5) == alive ? true : false };
                if (isAlive) {
                    // underpopulation
                    if (aliveNeighbors < 2) return dead;
                    // lives on happily
                    else if (aliveNeighbors < 4) return alive;
                    // overpopulation
                    else return dead;
                }
                // reproduction
                else if (aliveNeighbors == 3) return alive;
                return dead;
            };
            break;
        default:
            throw std::logic_error("Bad rule selected");
            break;
    }
}

void Automata2DSquareModel::setOscillator() {
    assert(board.size() > 2 && begin(board)->size() > 2);
    for (auto rowIter = begin(board); rowIter != end(board); ++rowIter) {
        for (auto collIter = begin(*rowIter); collIter != end(*rowIter); ++collIter) {
            *collIter = deadInternal;
        }
    }
    auto rowIterBegin {std::next(begin(board), 2)};
    auto rowIterEnd {std::next(begin(board), 3)};
    auto collIterBegin {std::next(rowIterBegin->begin(), 2)};
    auto collIterEnd {std::next(rowIterBegin->begin(), 5)};
    for (auto rowIter = rowIterBegin; rowIter != rowIterEnd; ++rowIter) {
        for (auto collIter = collIterBegin; collIter != collIterEnd; ++collIter) {
            *collIter = aliveInternal;
        }
    }
}