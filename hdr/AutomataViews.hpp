#pragma once

#include <fstream>
#include <memory>

class AutomataModelInterface;
class Automata1DModel;

class AutomataViewInterface {
    public:
        virtual void writeBoard() const = 0;
        virtual ~AutomataViewInterface() = default;
    //protected:
        std::weak_ptr<Automata1DModel> model_ptr;
};

class Automata1DConsoleWriter : public AutomataViewInterface {
    public:
        Automata1DConsoleWriter(std::shared_ptr<Automata1DModel> ptr) {
            model_ptr.reset();
            model_ptr = std::weak_ptr<Automata1DModel> {ptr};
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