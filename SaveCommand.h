#pragma once
#include "CommandInterface.h"

/**
 * @class SaveCommand
 * @brief Команда для сохранения изображения.
 */
class SaveCommand : public Command
{
public:
    explicit SaveCommand(Controller& controller) : Command(controller) { }

    void execute() const override
    {
        std::string filename = _controller.view.getUserInput("Введите название файла (с расширением) для сохранения: ");
        _controller.image.savePPM(filename);
        _controller.view.displayMessage(std::string("Файл сохранен успешно.\n"));
    }
    void info() const override
    {
        _controller.view.displayMessage(std::string("save - сохранить данные в файл;"));
    }
};