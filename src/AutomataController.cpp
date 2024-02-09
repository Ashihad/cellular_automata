#include "AutomataControllers.hpp"
#include "Exceptions.hpp"

class Automata1DConsoleWriter;
class Automata1DFileWriter;

void AutomataController::setView(const ViewMode mode, const std::string filename) {
    if (model_ptr == nullptr) throw std::logic_error("You need to set Model before setting ViewMode");
    switch (mode) {
        case ViewMode::Filemode:
            if (filename != "") view_ptr.reset(new Automata1DFileWriter(model_ptr, filename));
            else view_ptr.reset(new Automata1DFileWriter(model_ptr, "file.txt"));
            break;
        case ViewMode::Printmode:
            view_ptr.reset(new Automata1DConsoleWriter(model_ptr));
            break;
        default:
            throw NotImplemented();
            break;
    }
}

void AutomataController::setModel(const Model mode, const size_t boardSize, const uint8_t rule_no) {
    switch (mode) {
        case Model::Basic1D:
            model_ptr.reset(new Automata1DModel(boardSize));
            model_ptr->setRule(rule_no);
            break;
        case Model::Square2D:
            throw NotImplemented();
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
