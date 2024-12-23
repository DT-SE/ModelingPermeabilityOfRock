/**
 * @file Image.h
 * @brief Заголовочный файл модуля для работы с изображениями PPM (Portable Pixmap).
 */
#pragma once
#include <vector>
#include <string>

/**
 * @struct Pixel
 * @brief Структура для представления пикселя.
 */
struct Pixel
{
    /**
    * @var unsigned char color
    * @brief Значение от 0 до 255.
    */
    unsigned char color;
    /**
    * @brief Конструктор по умолчанию
    */
    Pixel() : color(0) { };
};

/**
* @class Image
* @brief Класс для работы с изображениями PPM (Portable Pixmap).
*/
class Image
{
    //Высота столбца или размер изображения по Y.
    size_t _height;
    //Длинна строки или размер изображения по X.
    size_t _width;
    //Массив пикслелей изображения.
    std::vector<Pixel> _pixels;

public:
    /**
    * @brief Конструктор по умолчанию
    */
    Image() = default;

    /**
    * @brief Конструктор пустого изображения
    */
    Image(int height, int width);

    /**
    * @brief Оператор присваивания
    */
    Image& operator=(const Image&) = default;
    
    /**
    * @brief Обращается к пикселю на позиции (i, j) по ссылке
    * @param i Номер строки.
    * @param j Номер столбца.
    */
    Pixel& getPixel(int i, int j) noexcept;
    /**
    * @brief Возвращает значение пикселя на позиции (i, j)
    * @param i Номер строки.
    * @param j Номер столбца.
    */
    Pixel getPixel(int i, int j) const noexcept;

    /**
    * @brief Возвращает длинну изображения по X
    */
    size_t getWidth() const noexcept;
    /**
    * @brief Возвращает высоту изображения по Y
    */
    size_t getHeight() const noexcept;

    /**
    * @brief Считывает PMM изображение из файла
    * @param filename Относительный путь к файлу.
    */
    bool readPPM(const std::string& filename);
    /**
    * @brief Сохраняет PMM изображения в файла
    * @param filename Относительнй путь к файлу.
    */
    bool savePPM(const std::string& filename);

    /**
    * @brief Обрезает изображение
    * @param x Начальняя позиция по X отностительно исходного изображения
    * @param y Начальняя позиция по Y отностительно исходного изображения
    * @param newWidth Длина вырезаемого изображения по X
    * @param newHeight Высота вырезаемого изображения по Y
    * @details Позиция X = 0 и Y = 0 находится в левом нижнем углу
    */
    Image crop(int x, int y, int newWidth, int newHeight);
};