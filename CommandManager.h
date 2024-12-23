#pragma once
#include "CommandInterface.h"
#include <unordered_map>
#include <string>
#include <memory>

/**
 * @class CommandManager
 * @brief Менеджер комманд.
 */
class CommandManager {
private:
    std::unordered_map<std::string, std::shared_ptr<Command>> _commands;

public:
    void addCommand(const std::string& name, std::shared_ptr<Command> command)
    {
        _commands[name] = command;
    }

    void executeCommand(const std::string& name) const
    {
        auto it = _commands.find(name);
        if (it != _commands.end()) {
            it->second->execute();
        }
    }

    const auto& getCommands() const
    {
        return _commands;
    }
};