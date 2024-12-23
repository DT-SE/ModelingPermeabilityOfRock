#pragma once
#include "CommandInterface.h"

/**
 * @class CorrectCommand
 * @brief Команда для обработки изображения.
 */
class CorrectCommand : public Command
{
public:
    explicit CorrectCommand(Controller& controller) : Command(controller) { }

    void execute() const override
    {
        Field field = imageIntoField(_controller.image);
        field.correction();
        field.addBorders();
        _controller.image = fieldIntoImage(field);

        _controller.view.displayMessage(std::string("Файл обработан успешно.\n"));
    }
    void info() const override
    {
        _controller.view.displayMessage(std::string("correct - удаление замкнутых пор, удаление не сквозных путей и добавление границ;"));
    }

private:
    //Перевод изображения в поле
    static Field imageIntoField(const Image& img)
    {
        Field fld(img.getHeight(), img.getWidth());
        for (size_t i = 0; i < img.getHeight(); i++)
        {
            for (size_t j = 0; j < img.getWidth(); j++)
            {
                if (img.getPixel(i, j).color == 255)
                {
                    fld.getCell(i, j) = Cell::solid;
                }
            }
        }
        return fld;
    }

    //Перевод поля в изображение
    static Image fieldIntoImage(const Field& fld)
    {
        Image img(fld.getHeight(), fld.getWidth());
        for (size_t i = 0; i < fld.getHeight(); i++)
        {
            for (size_t j = 0; j < fld.getWidth(); j++)
            {
                if (fld.getCell(i, j) == Cell::solid)
                {
                    img.getPixel(i, j).color = 255;
                }
                else
                {
                    img.getPixel(i, j).color = 0;
                }
            }
        }
        return img;
    }
};