#pragma once
#include "CommandInterface.h"
#include <unordered_map>
#include <memory>

/**
 * @class HelpCommand
 * @brief Команда для демонстрации списка команд.
 */
class HelpCommand : public Command
{
private:
    const std::unordered_map<std::string, std::shared_ptr<Command>>& _commands;

public:
    HelpCommand(Controller& controller, const std::unordered_map<std::string, std::shared_ptr<Command>>& cmds) : Command(controller), _commands(cmds) { }

    void execute() const override
    {
        _controller.view.displayMessage(std::string("________________________________________________________________"));
        _controller.view.displayMessage(std::string("Доступные команды:\n"));
        for (const auto& pair : _commands) {
            pair.second->info();
        }
        _controller.view.displayMessage(std::string("________________________________________________________________\n"));
    }
    void info() const override
    {
        _controller.view.displayMessage(std::string("help - список команд;"));
    }
};