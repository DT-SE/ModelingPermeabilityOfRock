#include "Field.h"
#include <iostream>


Field::Field(int height, int width) : _height(height), _width(width), _cells(_width* _height, Cell::nan) { };

Cell& Field::getCell(int i, int j) noexcept
{
    return _cells[i * _width + j];
}

inline Cell Field::getCell(int i, int j) const noexcept
{
    return _cells[i * _width + j];
}

size_t Field::getWidth() const noexcept
{
    return _width;
}

size_t Field::getHeight() const noexcept
{
    return _height;
}

//  Удаление замкнутых пор
void Field::correction() noexcept
{
    infectionAlgorithm();
}

//  Добавление нижней и верхней границ
void Field::addBorders()
{
    std::vector<Cell> border(_width, Cell::solid);
    _cells.insert(_cells.begin(), border.begin(), border.end());
    _cells.insert(_cells.end(), border.begin(), border.end());
    _height += 2;
}

//  Вывод (для отладки)
//void Field::print() const
//{
//    for (size_t i = 0; i < _height; i++)
//    {
//        for (size_t j = 0; j < _width; j++)
//        {
//            std::cout << static_cast<int>(getCell(i, j)) << " ";
//        }
//        std::cout << "\n";
//    }
//    std::cout << "\n";
//}

//  Алгоритм "Заражения" для удаления замкнутых пор
void Field::infectionAlgorithm() noexcept
{
    std::vector<bool> flags(_width * _height, false);
    std::vector<std::pair<int, int>> pool;

    //Поры левой границы
    for (size_t i = 0; i < _height; i++)
    {
        if (getCell(i, 0) != Cell::solid)
        {
            getCell(i, 0) = Cell::pore;
            pool.push_back(std::make_pair(i, 0));
            flags[i * _width] = true;
        }
    }

    //Заполнение доступных пор
    while (!pool.empty())
    {
        std::pair<int, int> pos = pool.back();
        pool.pop_back();
        const int i = pos.first;
        const int j = pos.second;

        if (isNecessaryNeighbor(i - 1, j, flags)) pool.push_back(std::make_pair(i - 1, j));
        if (isNecessaryNeighbor(i + 1, j, flags)) pool.push_back(std::make_pair(i + 1, j));
        if (isNecessaryNeighbor(i, j - 1, flags)) pool.push_back(std::make_pair(i, j - 1));
        if (isNecessaryNeighbor(i, j + 1, flags)) pool.push_back(std::make_pair(i, j + 1));

        getCell(i, j) = Cell::pore;
    }

    //Заполнение не доступных пор солидами
    for (size_t n = 0; n < _width * _height; n++)
    {
        if (_cells[n] == Cell::nan) _cells[n] = Cell::solid;
    }

    //Проверка на сквозное течение
    size_t i = 0;
    while (i < _height)
    {
        if (getCell(i, 0) != Cell::solid)
        {
            through(std::make_pair(i, 0));
            while (i + 1 < _height && getCell(i + 1, 0) != Cell::solid)
            {
                i++;
            }
        }
        i++;
    }
}

//Удаление не сквазных путей  
void Field::through(const std::pair<int, int>& pos) noexcept
{
    std::vector<bool> flags(_width * _height, false);
    std::vector<std::pair<int, int>> pool;

    pool.push_back(pos);

    bool is_through = false;
    while (!pool.empty())
    {
        std::pair<int, int> pos = pool.back();
        pool.pop_back();
        const int i = pos.first;
        const int j = pos.second;

        if (isPore(i - 1, j, flags)) pool.push_back(std::make_pair(i - 1, j));
        if (isPore(i + 1, j, flags)) pool.push_back(std::make_pair(i + 1, j));
        if (isPore(i, j - 1, flags)) pool.push_back(std::make_pair(i, j - 1));
        if (isPore(i, j + 1, flags)) pool.push_back(std::make_pair(i, j + 1));

        if (j == _width - 1)   is_through = true;
    }

    if (is_through) return;

    for (size_t i = 0; i < _height; i++)
    {
        for (size_t j = 0; j < _width; j++)
        {
            if (flags[i * _width + j])
            {
                getCell(i, j) = Cell::solid;
            }
        }
    }

    return;
}

//  Проверка условия, подходит ли сосед ячейки для обработки
inline bool Field::isPore(int i, int j, std::vector<bool>& flags) const noexcept
{
    if (i < 0 || i >= _height || j < 0 || j >= _width)
    {
        return false;
    }

    bool flags_before = flags[i * _width + j];
    flags[i * _width + j] = true;
    return !flags_before && getCell(i, j) == Cell::pore;
}

//  Проверка условия, подходит ли сосед ячейки для обработки
inline bool Field::isNecessaryNeighbor(int i, int j, std::vector<bool>& flags) const noexcept
{
    if (i < 0 || i >= _height || j < 0 || j >= _width)
    {
        return false;
    }

    bool flags_before = flags[i * _width + j];
    flags[i * _width + j] = true;
    return !flags_before && getCell(i, j) == Cell::nan;
}

////  Проверка условия, подходит ли сосед ячейки для обработки
//inline bool Field::isCheck(bool& state_cell, bool conditions) const noexcept
//{
//    bool state_cell_temp = state_cell;
//    state_cell = true;
//    return !state_cell_temp && conditions;
//}
//
////  Проверка условия, подходит ли сосед ячейки для обработки
//inline bool Field::isPore(int i, int j) const noexcept
//{
//    if (i < 0 || i >= _height || j < 0 || j >= _width)
//    {
//        return false;
//    }
//    return getCell(i, j) == Cell::pore;
//}
//
////  Проверка условия, подходит ли сосед ячейки для обработки
//inline bool Field::isNan(int i, int j) const noexcept
//{
//    if (i < 0 || i >= _height || j < 0 || j >= _width)
//    {
//        return false;
//    }
//    return getCell(i, j) == Cell::nan;
//}f (isCheck(flags[(pos.first - 1) * _width + pos.second], isPore(pos.first - 1, pos.second)) pool.push_back(std::make_pair(pos.first - 1, pos.second));