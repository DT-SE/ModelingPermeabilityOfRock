#pragma once
#include "DiagonalMatrix.h"
#include <cmath>


template <MatrixRule MatrixType>
class Solver
{
	MatrixType _A;
	Vector _b;
	size_t count_iter;

    // Параметры задачи
    const int _nx;   // Число узлов по x
    const int _ny;   // Число узлов по y
    const double _lx;   // Размер области по x
    const double _ly;   // Размер области по y

public:

    inline static double alpha = 1.0;       // Параметр Узавы
    inline static double tolerance = 1e-6;  // Точность
    inline static int max_iter = 100;       // Максимальное число итераций

	Solver(const MatrixType& A, const Vector& b, size_t nx, size_t ny, double lx, double ly) : _A(A), _b(b), _nx(nx), _ny(ny), _lx(lx), _ly(ly), count_iter(0) { }

    std::tuple<Vector, Vector> solving(double left_border_p, double right_border_p)
    {
        // Параметры сетки
        const int n = _nx * _ny;
        const double dx = _lx / (_nx - 1);
        const double dy = _ly / (_ny - 1);

        // Векторы скорости (u, v) и давления (p)
        Vector u(std::vector<double>(n, 0.0)), v(u), p(u);

        for (int i = 0; i < _ny; ++i)
        {
            p[i * _nx] = left_border_p;
            p[(i + 1) * _nx - 1] = right_border_p;
        }

        // Итерационный процесс метода Узавы
        for (int iter = 0; iter < max_iter; ++iter)
        {


            // Решение для скорости u и v с использованием метода сопряженных градиентов
            Vector rhs_u(_b);
            for (int i = 0; i < n; ++i)
            {
                rhs_u[i] -= _A.getElem(i, i) * p[i];
            }
            u = conjugateGradient(_A, rhs_u);

            Vector rhs_v(_b);
            for (int i = 0; i < n; ++i)
            {
                rhs_v[i] -= _A.getElem(i, i) * p[i];
            }
            v = conjugateGradient(_A, rhs_v);

            // Обновление давления
            Vector div_u(std::vector<double>(n, 0.0));
            for (int j = 0; j < _ny; ++j)
            {
                for (int i = 0; i < _nx; ++i)
                {
                    int index = idx(i, j, _nx);
                    if (i < _nx - 1) div_u[index] += (u[idx(i + 1, j, _nx)] - u[index]) / dx;
                    if (j < _ny - 1) div_u[index] += (v[idx(i, j + 1, _nx)] - v[index]) / dy;
                }
            }
            p += div_u * alpha;

            // Проверка сходимости
            double div_norm = div_u.norma();;
        }

        return std::tuple{ u, v };
    }

	size_t getIteratin() const noexcept
	{
		return count_iter;
	}

private:

    // Вычисление индекса в 1D массиве для 2D сетки
    inline int idx(int i, int j, int _nx)
    {
        return j * _nx + i;
    }

    // Метод сопряженных градиентов
    Vector conjugateGradient(const DiagonalMatrix& A, const Vector& b)
    {
        int n = b.size();
        Vector x(std::vector<double>(n, 0.0));  // Начальное приближение (нулевой вектор)
        Vector r(b);      // Невязка r = b - A * x (x = 0, поэтому r = b)
        Vector p(r);      // Начальное направление
        double rsold = r.norma_sqr();

        for (int iter = 0; iter < max_iter; ++iter)
        {
            // Вычисляем A * p
            Vector Ap(std::vector<double>(n, 0.0));

            Ap += A * p;

            // Вычисляем шаг alpha
            double pAp = Ap * p;

            double alpha = rsold / pAp;

            // Обновляем x и r
            x += p * alpha;
            r -= Ap * alpha;

            // Проверка сходимости
            double rsnew = r.norma_sqr();

            if (std::sqrt(rsnew) < tolerance)
            {
                break;
            }

            // Вычисляем новое направление p
            double beta = rsnew / rsold;
            p = r + p * beta;
            rsold = rsnew;
        }

        return x;
    }
};