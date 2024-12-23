#pragma once
#include "CommandInterface.h"

/**
 * @class OpenCommand
 * @brief Команда для запуска подпрограммы для .
 */
class FileCommand : public Command
{
public:
    explicit FileCommand(Controller& controller) : Command(controller) { }

    void execute() const override
    {
        std::string filename = _controller.view.getUserInput("Введите название файла (с расширением): ");
        _controller.image.readPPM(filename);
        _controller.view.clearScreen();
        _controller.view.displayMessage(std::string("Файл открыт успешно.\n"));
        _controller.commandFile();
        _controller.view.displayMessage(std::string("Введите help для просмотра списка команд.\n"));
    }
    void info() const override
    {
        _controller.view.displayMessage(std::string("file - запуск подпрограммы для работы с сегментированными цифровыми изображениями горной породы;"));
    }
};