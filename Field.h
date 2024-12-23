#pragma once
#include <vector>

/**
 * @brief Состояние ячейки
 */
enum class Cell : uint8_t
{
    /**
     * @brief Неопределенное состояние ячейки.
     */
    nan,
    /**
     * @brief Непроницаемая ячейка.
     */
    solid,
    /**
     * @brief Проницаемая ячейка.
     */
    pore
};

/**
 * @class Field
 * @brief Класс для обработки двумерного среза керна.
 */
class Field
{
    //Высота столбца или размер поля по Y.
    size_t _height;
    //Длинна строки или размер поля по X.
    size_t _width;
    //Массив ячеек поля
    std::vector<Cell> _cells;

public:

    /**
    * @brief Конструктор пустого поля
    */
    Field(int height, int width);

    /**
    * @brief Обращается к ячейке на позиции (i, j) по ссылке
    * @param i Номер строки.
    * @param j Номер столбца.
    */
    Cell& getCell(int i, int j) noexcept;
    /**
    * @brief Возвращает значение ячейки на позиции (i, j)
    * @param i Номер строки.
    * @param j Номер столбца.
    */
    inline Cell getCell(int i, int j) const noexcept;

    /**
    * @brief Возвращает длинну поля по X
    */
    size_t getWidth() const noexcept;
    /**
    * @brief Возвращает высоту поля по Y
    */
    size_t getHeight() const noexcept;

    /**
    * @brief Удаляет замкнутые поры и не сквозные пути
    */
    void correction() noexcept;

    /**
    * @brief Добавляет слой твердых ячеек на верхней и нижней границах
    */
    void addBorders();

    //  Вывод (для отладки)
    //void print() const;

private:

    //Алгоритм "Заражения" для удаления замкнутых пор
    void infectionAlgorithm() noexcept;
    //Удаление не сквазных путей  
    void through(const std::pair<int, int>& pos) noexcept;
    //Проверка ячейки на пору с пометой
    inline bool isPore(int i, int j, std::vector<bool>& flags) const noexcept;
    //Проверка условия, подходит ли сосед ячейки для обработки с пометкой
    inline bool isNecessaryNeighbor(int i, int j, std::vector<bool>& flags) const noexcept;
};