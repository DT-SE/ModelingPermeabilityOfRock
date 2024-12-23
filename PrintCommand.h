#pragma once
#include "CommandInterface.h"

/**
 * @class PrintCommand
 * @brief Команда для вывода изображения.
 */
class PrintCommand : public Command
{
public:
    explicit PrintCommand(Controller& controller) : Command(controller) { }

    void execute() const override
    {
        _controller.view.displayMessage(std::string("Длина изображения: ") + std::to_string(_controller.image.getWidth()));
        _controller.view.displayMessage(std::string("Высота изображения: ") + std::to_string(_controller.image.getHeight()));
        print();
    }
    void info() const override
    {
        _controller.view.displayMessage(std::string("print - вывести содержимое файла;"));
    }

private:
    void print() const
    {
        std::string message;
        for (size_t i = 0; i < _controller.image.getHeight(); i++)
        {
            for (size_t j = 0; j < _controller.image.getWidth(); j++)
            {
                message.append(std::to_string(static_cast<int>(_controller.image.getPixel((_controller.image.getHeight() - 1) - i, j).color)) + "\t");
            }
            message.append("\n");
        }
        message.append("\n");

        _controller.view.displayMessage(message);
    }
};