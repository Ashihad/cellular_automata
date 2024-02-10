#pragma once

#include <fstream>
#include <memory>

class AutomataModelInterface;
class Automata1DModel;
class Automata2DSquareModel;

class AutomataViewInterface {
    public:
        virtual ~AutomataViewInterface() = default;
        virtual void writeBoard() = 0;
        virtual std::string getTag() = 0;
    protected:
        char aliveSymbol {'O'};
        char deadSymbol {'.'};
};

class Automata1DConsoleWriter : public AutomataViewInterface {
    public:
        Automata1DConsoleWriter(std::shared_ptr<Automata1DModel>);
        virtual ~Automata1DConsoleWriter() = default;
        virtual void writeBoard() override;
        virtual std::string getTag() override;
    protected:
        std::weak_ptr<Automata1DModel> model_ptr;
    private:
        const std::string tag {"1D"};
};

class Automata1DFileWriter : public AutomataViewInterface {
    public:
        Automata1DFileWriter(std::shared_ptr<Automata1DModel>, const std::string);
        virtual ~Automata1DFileWriter() = default;
        virtual void writeBoard() override;
        virtual std::string getTag() override;
    protected:
        std::weak_ptr<Automata1DModel> model_ptr;
    private:
        const std::string tag {"1D"};
        std::ofstream writeStream;
};

class Automata2DSquareConsoleWriter : public AutomataViewInterface {
    public:
        Automata2DSquareConsoleWriter(std::shared_ptr<Automata2DSquareModel>);
        virtual ~Automata2DSquareConsoleWriter() = default;
        virtual void writeBoard() override;
        virtual std::string getTag() override;
    protected:
        std::weak_ptr<Automata2DSquareModel> model_ptr;
    private:
        const std::string tag {"2D"};
};