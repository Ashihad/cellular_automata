#pragma once
#include "AutomataViews.hpp"

#include <vector>
#include <cstddef>
#include <istream>
#include <memory>
#include <functional>

using Board1DType = std::vector<char>;

// class AutomataModelInterface {
//     public:
//         virtual ~AutomataModelInterface() = default;

//         virtual void nextState() = 0;
// };

class Automata1DModel {//: public AutomataModelInterface {
    public:
        Automata1DModel(const std::size_t);
        virtual ~Automata1DModel() = default;

        virtual void nextState() ;//override;
        virtual void setRule(const uint8_t);

        inline void setBoard(Board1DType newBoard) {board = newBoard;};
        inline Board1DType& getBoard() {return board;};
    private:
        Board1DType board;
        Board1DType tmpBoard;
        std::function<char(char, char, char)> rule;
};