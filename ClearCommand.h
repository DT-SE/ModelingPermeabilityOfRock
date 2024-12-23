#pragma once
#include "CommandInterface.h"

/**
 * @class ClearCommand
 * @brief Команда для очистки экрана.
 */
class ClearCommand : public Command
{
public:
    explicit ClearCommand(Controller& controller) : Command(controller) { }

    void execute() const override
    {
        _controller.view.clearScreen();
    }
    void info() const override
    {
        _controller.view.displayMessage(std::string("clear - очистка консоли;"));
    }
};