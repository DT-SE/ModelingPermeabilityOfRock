#pragma once
#include "CommandInterface.h"

/**
 * @class OpenCommand
 * @brief Команда для открытия файла.
 */
class OpenCommand : public Command
{
public:
    explicit OpenCommand(Controller& controller) : Command(controller) { }

    void execute() const override
    {
        std::string filename;
        filename = _controller.view.getUserInput("Введите название другого файла (с расширением): ");
        _controller.image.readPPM(filename);
        _controller.view.displayMessage(std::string("Файл открыт успешно.\n"));
    }
    void info() const override
    {
        _controller.view.displayMessage(std::string("open - открыть файла;"));
    }
};