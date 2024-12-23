/* @mainpage My Personal Index Page
 *
 * @section intro_sec Introduction
 *
 * This is the introduction.
 *
 * @section install_sec Installation
 *
 * @subsection step1 Step 1: Opening the box
 *
 * etc...
 */

#include "Controller.h"
#include "DiagonalMatrix.h"
#include "Solver.h"

namespace
{
    static constexpr double PI = 3.14159265358979323846;
    static constexpr double PI_SQR = PI * PI;
}

void test()
{
    // Параметры задачи
    const int nx = 16;       // Число узлов по x
    const int ny = 16;       // Число узлов по y
    const int n = nx * ny;
    const double lx = 1.0;   // Размер области по x
    const double ly = 1.0;   // Размер области по y
    const double nu = 0.01;  // Вязкость
    const double dx = lx / (nx - 1);
    const double dy = ly / (ny - 1);



    // Матрица Лапласиана
    double anti_square_hx = 1.0 / (dx * dx);
    double anti_square_hy = 1.0 / (dy * dy);
    DiagonalMatrix A = make5DiagonalMatrix(nx, ny, nu * 2.0 * (anti_square_hx + anti_square_hy), -nu * anti_square_hx, -nu * anti_square_hy);

    Vector b(std::vector<double>(nx * ny, 0));
    for (size_t i = 0; i < b.size(); i++)
    {
        double pi_x = ((i % nx) + 1) * dx * PI;
        double pi_y = ((i / nx) + 1) * dy * PI;
        b[i] = 2 * PI_SQR * sin(pi_x) * sin(pi_y);
    }

    Solver solver(A, b, nx, ny, lx, ly);
    std::tuple<Vector, Vector> u_v = solver.solving(100000, 120000);

    {
        std::ofstream fout("u.raw", std::ios::binary | std::ios::trunc);
        fout.write((char*)std::get<0>(u_v).data(), sizeof(double) * std::get<0>(u_v).size());
    }

    {
        std::ofstream fout("v.raw", std::ios::binary | std::ios::trunc);
        fout.write((char*)std::get<1>(u_v).data(), sizeof(double) * std::get<1>(u_v).size());
    }
}


int main()
{
    //test();

    setlocale(LC_ALL, "Russian");
    Controller ctrl;
    ctrl.run();

    //DiagonalMatrix mtrx("SLAU_2.raw");
    //mtrx.print();
    //mtrx.write(std::filesystem::current_path() / "matrix_1.raw");

    return 0;
}