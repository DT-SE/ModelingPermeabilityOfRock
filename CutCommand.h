#pragma once
#include "CommandInterface.h"

/**
 * @class CutCommand
 * @brief Команда для обрезания изображения.
 */
class CutCommand : public Command
{
public:
    explicit CutCommand(Controller& controller) : Command(controller) { }

    void execute() const override
    {
        std::vector<std::string> params = _controller.view.getUserInputList("Введите параметры обрезки (через пробел) [x0, y0, new width, new height]: ");

        if (params.size() != 4)
        {
            throw std::runtime_error("Неверное количество аргументов");
        }
        int x = std::stoi(params[0]);
        int y = std::stoi(params[1]);
        int width = std::stoi(params[2]);
        int height = std::stoi(params[3]);

        _controller.image = _controller.image.crop(x, y, width, height);
        _controller.view.displayMessage(std::string("Файл обрезан успешно.\n"));
    }
    void info() const override
    {
        _controller.view.displayMessage(std::string("cut - вырезать содержимое файла;"));
    }
};