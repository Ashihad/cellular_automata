#pragma once
#include "AutomataViews.hpp"

#include <vector>
#include <functional>

using Board1DType = std::vector<char>;
using Board2DType = std::vector<std::vector<char>>;

class AutomataModelInterface {
    public:
        virtual void nextState() = 0;
};

class Automata1DModel : public AutomataModelInterface {
    public:
        Automata1DModel(const std::size_t);
        virtual ~Automata1DModel() = default;

        virtual void nextState() override;
        virtual void setRule(const uint8_t);

        inline void setBoard(Board1DType newBoard) { board = newBoard; };
        inline Board1DType& getBoard() { return board; };
        const std::string tag {"1D"};
        char aliveInternal {'1'};
        char deadInternal {'0'};
    private:
        Board1DType board;
        Board1DType tmpBoard;
        std::vector<char> neighborhood;
        std::function<char(std::vector<char>&)> rule;
};

enum class Rule2D {
    Conway
};

class Automata2DSquareModel : public AutomataModelInterface {
    public:
        Automata2DSquareModel(const std::size_t, const std::size_t);
        Automata2DSquareModel(const std::size_t);
        virtual ~Automata2DSquareModel() = default;

        virtual void nextState() override;
        virtual void setRule(Rule2D);

        inline void setBoard(Board2DType newBoard) { board = newBoard; };
        inline Board2DType& getBoard() { return board; };

        void setOscillator();
        const std::string tag {"2D"};
        char aliveInternal {'1'};
        char deadInternal {'0'};
    private:
        Board2DType board;
        Board2DType tmpBoard;
        std::vector<char> neighborhood;
        std::function<char(std::vector<char>&)> rule;
};