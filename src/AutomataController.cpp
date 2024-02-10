#include "AutomataControllers.hpp"
#include "Exceptions.hpp"
#include "AutomataModels.hpp"

#include <iostream>

class Automata1DConsoleWriter;
class Automata1DFileWriter;

void AutomataController::setView(const ViewMode mode, const std::string filename) {
    if (model_ptr == nullptr) throw std::logic_error("You need to set Model before setting ViewMode");
    switch (mode) {
        case ViewMode::Filemode:
            if (filename != "") {
                view_ptr.reset( new Automata1DFileWriter(std::dynamic_pointer_cast<Automata1DModel>(model_ptr), 
                                filename));
            }
            else {
                view_ptr.reset( new Automata1DFileWriter(std::dynamic_pointer_cast<Automata1DModel>(model_ptr),
                                "file.txt"));
            }

            if (view_ptr->getTag() != currentTag) throw std::logic_error("Mismatch between dimentiality of model and view detected");
            break;
        case ViewMode::Printmode:
            view_ptr.reset(new Automata1DConsoleWriter(std::dynamic_pointer_cast<Automata1DModel>(model_ptr)));
            
            if (view_ptr->getTag() != currentTag) throw std::logic_error("Mismatch between dimentiality of model and view detected");
            break;
        case ViewMode::Printmode2D:
            view_ptr.reset(new Automata2DSquareConsoleWriter(std::dynamic_pointer_cast<Automata2DSquareModel>(model_ptr)));
            
            if (view_ptr->getTag() != currentTag) throw std::logic_error("Mismatch between dimentiality of model and view detected");
            break;
        default:
            throw NotImplemented();
            break;
    }
}

void AutomataController::setModel(const Model mode, const size_t boardSize, const uint8_t rule_no) {
    switch (mode) {
        case Model::Basic1D:
            currentTag = "1D";
            model_ptr.reset(new Automata1DModel(boardSize)); 
            std::dynamic_pointer_cast<Automata1DModel>(model_ptr)->setRule(rule_no);
            break;
        case Model::Square2D:
            currentTag = "2D";
            model_ptr.reset(new Automata2DSquareModel(boardSize)); 
            break;
        default:
            throw std::invalid_argument("Bad Model selected");
            break;
    }
}

void AutomataController::runModel(const unsigned int iters) const {
    view_ptr->writeBoard();
    for (unsigned int i = 0; i < iters; ++i) {
        model_ptr->nextState();
        view_ptr->writeBoard();
    }
}
