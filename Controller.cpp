#include "Controller.h"

#include "HelpCommand.h"
#include "ExitCommand.h"
#include "ClearCommand.h"
#include "CorrectCommand.h"
#include "CutCommand.h"
#include "OpenCommand.h"
#include "PrintCommand.h"
#include "SaveCommand.h"
#include "FileCommand.h"

#include "CommandManager.h"
#include <stdexcept>


void Controller::run()
{
    CommandManager manager;

    // Добавляем команды
    manager.addCommand("help", std::make_shared<HelpCommand>(*this, manager.getCommands()));
    manager.addCommand("clear", std::make_shared<ClearCommand>(*this));
    manager.addCommand("exit", std::make_shared<ExitCommand>(*this));
    manager.addCommand("file", std::make_shared<FileCommand>(*this));

    std::string input;

    view.displayMessage(std::string("Введите help для просмотра списка команд.\n"));
    while (true)
    {
        try
        {
            input = view.getUserInput("~ ");
            manager.executeCommand(input);

            if (input == "exit")
            {
                break;
            }
        }
        catch (const std::exception& e)
        {
            view.displayMessage(std::string("Ошибка: ") + e.what());
            view.displayMessage(std::string("Попробуйте снова.\n"));
        }
    }
}

//Цикл подпрограммы
void Controller::commandFile()
{
    CommandManager manager;

    // Добавляем команды
    manager.addCommand("help", std::make_shared<HelpCommand>(*this, manager.getCommands()));
    manager.addCommand("clear", std::make_shared<ClearCommand>(*this));
    manager.addCommand("exit", std::make_shared<ExitCommand>(*this));
    //manager.addCommand("open", std::make_shared<OpenCommand>(*this));
    manager.addCommand("print", std::make_shared<PrintCommand>(*this));
    manager.addCommand("cut", std::make_shared<CutCommand>(*this));
    manager.addCommand("correct", std::make_shared<CorrectCommand>(*this));
    manager.addCommand("save", std::make_shared<SaveCommand>(*this));

    std::string input;

    view.displayMessage(std::string("Введите help для просмотра списка команд.\n"));
    while (true)
    {
        try
        {
            input = view.getUserInput("file~ ");
            manager.executeCommand(input);

            if (input == "exit")
            {
                break;
            }
        }
        catch (const std::exception& e)
        {
            view.displayMessage(std::string("Ошибка: ") + e.what());
            view.displayMessage(std::string("Попробуйте снова.\n"));
        }
    }
}