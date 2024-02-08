#pragma once
#include "AutomataModels.hpp"
#include "AutomataViews.hpp"

// each enum value represents different output mode 
enum class ViewMode {
    Filemode,
    Printmode
};

// each enum value represents different model 
enum class Model {
    Basic1D,
    Square2D
};

class AutomataControllerInterface {
    public:
        virtual ~AutomataControllerInterface() = default;
        virtual void setView(const ViewMode) = 0;
        virtual void setModel(const Model, const size_t, const uint8_t) = 0;
        virtual void runModel(const unsigned int) = 0;
    protected:
        std::unique_ptr<AutomataViewInterface> view_ptr;
        std::shared_ptr<Automata1DModel> model_ptr;
};

class AutomataController final : public AutomataControllerInterface {
    public:
        AutomataController() = default;
        virtual ~AutomataController() = default;

        virtual void setView(const ViewMode) override;
        virtual void setModel(const Model, const size_t, const uint8_t) override;
        virtual void runModel(const unsigned int) override;
};