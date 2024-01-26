#pragma once

#include <fstream>
#include <memory>

class AutomataModelInterface;
class Automata1DModel;

class AutomataViewInterface {
    public:
        virtual void writeBoard() const = 0;
    //protected:
        std::shared_ptr<Automata1DModel> model_ptr;
};

class Automata1DConsoleWriter : public AutomataViewInterface {
    public:
        Automata1DConsoleWriter(Automata1DModel* ptr) {
            model_ptr.reset(ptr);
        }
        virtual void writeBoard() const override;
};

// class Automata1DFileWriter : public AutomataViewInterface {
//     public:
//         Automata1DFileWriter(Automata1DModel* ptr, const std::string&);
//         virtual void writeBoard() const override;
//     private:
//         std::ofstream writeStream;
// };