#include "AutomataControllers.hpp"
#include "Exceptions.hpp"
#include "AutomataModels.hpp"

#include <iostream>

class Automata1DConsoleWriter;
class Automata1DFileWriter;

AutomataController::AutomataController( const Model modelType, 
                                        const size_t boardSize,
                                        const ViewMode viewType) {
    switch (modelType) {
        case Model::Basic1D:
            currentTag = "1D";
            model_ptr.reset(new Automata1DModel(boardSize)); 
            // default rule is 90 because i like it, fight me
            std::dynamic_pointer_cast<Automata1DModel>(model_ptr)->setRule(90);
            break;
        case Model::Square2D:
            currentTag = "2D";
            model_ptr.reset(new Automata2DSquareModel(boardSize)); 
            break;
        default:
            throw std::invalid_argument("Bad Model selected");
            break;
    }

    switch (viewType) {
        case ViewMode::Filemode:
            if (currentTag == "1D")
                view_ptr.reset( new Automata1DFileWriter(std::dynamic_pointer_cast<Automata1DModel>(model_ptr),
                                "file.txt"));
            else if (currentTag == "2D") 
                throw NotImplemented("No FileMode for square 2D automatas yet");
            break;
        case ViewMode::Printmode:
            if (currentTag == "1D")
                view_ptr.reset(new Automata1DConsoleWriter(std::dynamic_pointer_cast<Automata1DModel>(model_ptr)));
            else if (currentTag == "2D")
                view_ptr.reset(new Automata2DSquareConsoleWriter(std::dynamic_pointer_cast<Automata2DSquareModel>(model_ptr)));            
            break;
        default:
            throw NotImplemented();
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

void AutomataController::setRule(const uint8_t rule_no) {
    if (currentTag != "1D") throw std::logic_error("Can't set rule with 8 bit number if model is not one dimentional");
    std::dynamic_pointer_cast<Automata1DModel>(model_ptr)->setRule(rule_no);
}

void AutomataController::setRule(const Rule2D rule_enum) {
    if (currentTag != "2D") throw std::logic_error("Can't set rule with Rule2D enum if model is not two dimentional");
    std::dynamic_pointer_cast<Automata2DSquareModel>(model_ptr)->setRule(rule_enum);
}