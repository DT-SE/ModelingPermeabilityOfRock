#pragma once
#include "Controller.h"
#include <stdexcept>

/**
 * @class Command
 * @brief Интерфейс для команд.
 */
class Command
{
protected:
    Controller& _controller;

public:
    Command(Controller& controller) : _controller(controller) { }

    virtual ~Command() = default;
    virtual void execute() const = 0;
    virtual void info() const = 0;
};