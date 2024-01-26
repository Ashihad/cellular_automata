#pragma once
#include "AutomataViews.hpp"

#include <vector>
#include <cstddef>
#include <istream>
#include <memory>
#include <functional>

using Board1DType = std::vector<char>;

class AutomataModelInterface {
    public:
        virtual void nextState() = 0;
        virtual ~AutomataModelInterface = default;
};

class Automata1DModel : public AutomataModelInterface {
    public:
        Automata1DModel(std::size_t size);
        virtual void nextState() override;

        inline void setBoard(Board1DType newBoard) {board = newBoard;};
        inline Board1DType& getBoard() {return board;};
    private:
        Board1DType board;
};