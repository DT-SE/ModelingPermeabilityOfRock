#include "ConsoleView.h"
#include <iostream>
#include <sstream>
#include <cstdlib>

void ConsoleView::displayMessage(const std::string& message) const
{
    std::cout << message << std::endl;
}

std::string ConsoleView::getUserInput(const std::string& prompt) const
{
    std::cout << prompt;
    std::string input;
    std::getline(std::cin, input);
    return input;
}

void ConsoleView::clearScreen() const
{
    system("cls");
}

std::vector<std::string> ConsoleView::getUserInputList(const std::string& prompt) const
{
    std::cout << prompt;
    std::string input;
    std::getline(std::cin, input);

    std::stringstream ss(input);
    std::string word;
    std::vector<std::string> words; // Вектор для хранения слов

    // Разбиваем строку на слова по пробелам
    while (ss >> word) {
        words.push_back(word);
    }
    return words;
}