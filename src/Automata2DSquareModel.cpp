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
    setShiftedOscillator();

    setRule(Rule2D::Conway);

}

void Automata2DSquareModel::nextState() {
    // reset tmpBoard
    for (auto& row : tmpBoard)
        std::fill(begin(row), end(row), deadInternal);

    auto iterRow = begin(board);
    auto tmpIterRow = begin(tmpBoard);
    for (; iterRow != end(board); ++iterRow, ++tmpIterRow) {
        auto iterColl = iterRow->begin();
        auto tmpIterColl = tmpIterRow->begin();
        for (; iterColl != iterRow->end(); ++iterColl, ++tmpIterColl) {
            // construct neighborhood
            std::size_t distance { static_cast<std::size_t>(std::distance(iterRow->begin(), iterColl)) };

            // this line ensures that previous row is either valid or last one
            auto previousRow { iterRow != begin(board) ? std::prev(iterRow) : std::prev(end(board))};
            // bound checking left-right
            neighborhood[0] = distance != 0 ? *std::next(previousRow->begin(), distance-1) : *std::prev(previousRow->end());
            neighborhood[1] = *std::next(previousRow->begin(), distance);
            neighborhood[2] = distance != iterRow->size()-1 ? *std::next(previousRow->begin(), distance+1): *(previousRow->begin());
            
            // bound checking left-right
            neighborhood[3] = distance != 0 ? *std::prev(iterColl) : *std::prev(iterRow->end());
            neighborhood[4] = *iterColl;
            neighborhood[5] = distance != iterRow->size()-1 ? *std::next(iterColl) : *(iterRow->begin());
            
            // this line ensures that next row is either valid or first one
            auto nextRow { iterRow != std::prev(end(board)) ? std::next(iterRow) : begin(board)};
            // bound checking left-right
            neighborhood[6] = distance != 0 ? *std::next(nextRow->begin(), distance-1) : *std::prev(nextRow->end());
            neighborhood[7] = *std::next(nextRow->begin(), distance);
            neighborhood[8] = distance != iterRow->size()-1 ? *std::next(nextRow->begin(), distance+1) : *(nextRow->begin());
            
            // get next state given a neighborhood
            *tmpIterColl = rule(neighborhood);
        }
    }
    // commit to next state
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
    // minimal size: 3x3
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

void Automata2DSquareModel::setShiftedOscillator() {
    // minimal size: 3x3
    assert(board.size() > 2 && begin(board)->size() > 2);
    for (auto rowIter = begin(board); rowIter != end(board); ++rowIter) {
        for (auto collIter = begin(*rowIter); collIter != end(*rowIter); ++collIter) {
            *collIter = deadInternal;
        }
    }
    auto rowIterBegin {begin(board)};
    auto rowIterEnd {std::next(begin(board), 1)};
    auto collIterBegin {rowIterBegin->begin()};
    auto collIterEnd {std::next(rowIterBegin->begin(), 2)};
    for (auto rowIter = rowIterBegin; rowIter != rowIterEnd; ++rowIter) {
        for (auto collIter = collIterBegin; collIter != collIterEnd; ++collIter) {
            *collIter = aliveInternal;
        }
    }
    auto lastToRight {std::prev(begin(board)->end())};
    *lastToRight = aliveInternal;
}