#pragma once
#include "CommandInterface.h"

/**
 * @class ExitCommand
 * @brief Команда для выхода из программы/подпрограммы.
 */
class ExitCommand : public Command
{
public:
    explicit ExitCommand(Controller& controller) : Command(controller) { }

    void execute() const override
    {
        _controller.view.clearScreen();
        return;
    }
    void info() const override
    {
        _controller.view.displayMessage(std::string("exit - завершение работы программы;"));
    }
};