#pragma once
#include "AutomataModels.hpp"
#include "AutomataViews.hpp"

#include <variant>

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
        std::string currentTag;
    protected:
        virtual void runModel(const unsigned int) const = 0;

        std::unique_ptr<AutomataViewInterface> view_ptr;
        std::shared_ptr<AutomataModelInterface> model_ptr;
};

class AutomataController final : public AutomataControllerInterface {
    public:
        AutomataController(const Model, const size_t, const ViewMode);
        virtual ~AutomataController() = default;

        virtual void runModel(const unsigned int) const override;
        virtual void setRule(const uint8_t);
        virtual void setRule(const Rule2D);

};