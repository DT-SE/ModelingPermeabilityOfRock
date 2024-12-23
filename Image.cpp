/**
 * @file Image.cpp
 * @brief Файл реализации модуля для работы с изображениями PPM (Portable Pixmap).
 */
#include "Image.h"
#include <fstream>

Image::Image(int height, int width) : _height(height), _width(width), _pixels(_width * _height) { }

Pixel& Image::getPixel(int i, int j) noexcept
{
    return _pixels[i * _width + j];
}

Pixel Image::getPixel(int i, int j) const noexcept
{
    return _pixels[i * _width + j];
}

size_t Image::getWidth() const noexcept
{
    return _width;
}

size_t Image::getHeight() const noexcept
{
    return _height;
}

// Чтение изображения PPM
bool Image::readPPM(const std::string& filename)
{
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Не удалось открыть файл");
    }

    file.read(reinterpret_cast<char*>(&_width), 8);
    file.read(reinterpret_cast<char*>(&_height), 8);

    _pixels.resize(_height * _width);
    for (size_t i = 0; i < _height; ++i) {
        for (size_t j = 0; j < _width; ++j) {
            file.read(reinterpret_cast<char*>(&getPixel(i, j).color), 1);
        }
    }
    return true;
}

// Сохранение изображения PPM
bool Image::savePPM(const std::string& filename)
{
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Не удалось открыть файл для записи");
    }

    file.write(reinterpret_cast<char*>(&_width), 8);
    file.write(reinterpret_cast<char*>(&_height), 8);

    for (size_t i = 0; i < _height; ++i) {
        for (size_t j = 0; j < _width; ++j) {
            file.write(reinterpret_cast<const char*>(&getPixel(i, j).color), 1);
        }
    }
    return true;
}

// Обрезка изображения (crop)
Image Image::crop(int x, int y, int newWidth, int newHeight)
{
    if (x < 0 || x + newWidth > _width || y < 0 || y + newHeight > _height || newWidth == 0 || newHeight == 0) {
        throw std::runtime_error("Не корректные параметры для обрезки изображения");
    }

    Image crop_image(newHeight, newWidth);
    for (int i = 0; i < newHeight; ++i) {
        for (int j = 0; j < newWidth; ++j) {
            crop_image.getPixel(i, j) = getPixel(y + i, x + j);
        }
    }

    return crop_image;
}