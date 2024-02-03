#pragma once
#include "AutomataModels.hpp"
#include "AutomataViews.hpp"

enum class ViewMode {
    Filemode,
    Printmode
};

enum class Model {
    Basic1D,
    Square2D
};

class AutomataControllerInterface {
    public:
        virtual ~AutomataControllerInterface() = default;
        
        virtual void setView(ViewMode) = 0;
        virtual void setModel(Model) = 0;
        virtual void runModel(unsigned int) = 0;
    protected:
        std::unique_ptr<AutomataViewInterface> view_ptr;
        std::shared_ptr<Automata1DModel> model_ptr;
};

class AutomataController final : public AutomataControllerInterface {
    public:
        AutomataController() = default;
        virtual ~AutomataController() = default;

        virtual void setView(ViewMode) override;
        virtual void setModel(Model) override;
        virtual void runModel(unsigned int) override;
};