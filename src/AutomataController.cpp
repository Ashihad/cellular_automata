#include "AutomataControllers.hpp"
#include "Exceptions.hpp"

void AutomataController::setView(ViewMode mode) {
    if (model_ptr == nullptr) throw std::logic_error("You need to set Model before setting ViewMode");
    switch (mode) {
        // case ViewMode::Filemode:
        //     view_ptr.reset(new Automata1DFileWriter(model_ptr.get(), "file.txt"));
        //     break;
        case ViewMode::Printmode:
            view_ptr.reset(new Automata1DConsoleWriter(model_ptr));
            break;
        default:
            throw NotImplemented();
            break;
    }
}

void AutomataController::setModel(Model mode) {
    switch (mode) {
        case Model::Basic1D:
            model_ptr.reset(new Automata1DModel(31));
            model_ptr->setRule(90);
            break;
        case Model::Square2D:
            throw NotImplemented();
            break;
        default:
            throw std::invalid_argument("Bad Model selected");
            break;
    }
}

void AutomataController::runModel(unsigned int iters) {
    view_ptr->writeBoard();
    for (unsigned int i = 0; i < iters; ++i) {
        model_ptr->nextState();
        view_ptr->writeBoard();
    }
}
