#pragma once
#include <vector>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iomanip>

//template <class double>
//concept Floatingdouble = std::is_floating_point_v<double>;


class Vector
{
	std::vector<double> _data;

public:

	Vector(std::filesystem::path file_path)
	{
		std::ifstream fin(file_path, std::ios::binary);
		if (!fin) {
			throw std::runtime_error("Не удалось открыть файл для чтения");
		}
		size_t size;
		fin.read((char*)&size, sizeof(size_t));
		_data.resize(size);
		fin.read((char*)_data.data(), sizeof(double) * size);
	}

	Vector(std::vector<double> vec) : _data(vec) { }

	Vector operator+(const Vector& other) const noexcept
	{
		std::vector<double> result(_data);

		for (size_t i = 0; i < _data.size(); i++)
		{
			result[i] += other._data[i];
		}

		return Vector{ result };
	}

	Vector& operator+=(const Vector& other) noexcept
	{
		for (size_t i = 0; i < _data.size(); i++)
		{
			_data[i] += other._data[i];
		}
		return *this;
	}

	Vector operator-(const Vector& other) const noexcept
	{
		std::vector<double> result(_data);

		for (size_t i = 0; i < _data.size(); i++)
		{
			result[i] -= other._data[i];
		}

		return Vector{ result };
	}

	Vector& operator-=(const Vector& other) noexcept
	{
		for (size_t i = 0; i < _data.size(); i++)
		{
			_data[i] -= other._data[i];
		}
		return *this;
	}

	double operator*(const Vector& other) const noexcept
	{
		double value = 0;
		for (size_t i = 0; i < _data.size(); i++)
		{
			value += _data[i] * other._data[i];
		}

		return value;
	}

	Vector operator*(double arg) const noexcept
	{
		std::vector<double> result(_data);

		for (size_t i = 0; i < _data.size(); i++)
		{
			result[i] *= arg;
		}

		return Vector{ result };
	}

	double& operator[](int index) noexcept
	{
		return _data[index];
	}

	double operator[](int index) const noexcept
	{
		return _data[index];
	}

	double* data() noexcept
	{
		return _data.data();
	}

	size_t size() const noexcept
	{
		return _data.size();
	}

	Vector& abs_modify() noexcept
	{
		for (size_t i = 0; i < _data.size(); i++)
		{
			_data[i] = std::abs(_data[i]);
		}
		return *this;
	}

	Vector abs() const noexcept
	{
		std::vector<double> result(_data);
		for (size_t i = 0; i < result.size(); i++)
		{
			result[i] = std::abs(result[i]);
		}
		return result;
	}

	double min() const noexcept
	{
		double min = std::numeric_limits<double>::max();
		for (size_t i = 0; i < _data.size(); i++)
		{
			min = _data[i] < min ? _data[i] : min;
		}
		return min;
	}

	double max() const noexcept
	{
		double max = std::numeric_limits<double>::min();
		for (size_t i = 0; i < _data.size(); i++)
		{
			max = _data[i] > max ? _data[i] : max;
		}
		return max;
	}

	double sum() const noexcept
	{
		double sum = 0;
		for (size_t i = 0; i < _data.size(); i++)
		{
			sum += _data[i];
		}
		return sum;
	}

	double mean() const noexcept
	{
		return sum() / _data.size();
	}

	double mean_sqr() const noexcept
	{
		double x_mean = mean();
		double x_mean_sqr = 0;

		for (size_t i = 0; i < _data.size(); i++)
		{
			x_mean_sqr += pow(_data[i] - x_mean, 2);
		}

		return pow(x_mean_sqr / _data.size(), 0.5);
	}

	double norma_sqr() const noexcept
	{
		return std::abs(*this * *this);
	}

	double norma() const noexcept
	{
		return pow(static_cast<double>(norma_sqr()), 0.5);
	}
};


class DiagonalMatrix
{
	size_t _order_of_matrix;
	size_t _block_size;
	std::vector<double> _main_diagonal;
	std::vector<double> _side_diagonal;
	std::vector<double> _upper_side_diagonal;

	DiagonalMatrix() = default;

public:
	DiagonalMatrix(std::filesystem::path file_path)
	{
		std::ifstream fin(file_path, std::ios::binary);
		if (!fin) {
			throw std::runtime_error("Не удалось открыть файл для чтения");
		}
		fin.read((char*)&_order_of_matrix, sizeof(size_t));
		fin.read((char*)&_block_size, sizeof(size_t));
		const size_t& n = _order_of_matrix;
		const size_t& m = _block_size;
		_main_diagonal.resize(n);
		_side_diagonal.resize(n - 1);
		_upper_side_diagonal.resize(n - m);
		fin.read((char*)_main_diagonal.data(), sizeof(double) * n);
		fin.read((char*)_side_diagonal.data(), sizeof(double) * (n - 1));
		fin.read((char*)_upper_side_diagonal.data(), sizeof(double) * (n - m));
	}

	DiagonalMatrix& operator*=(double arg) noexcept
	{
		for (size_t i = 0; i < _order_of_matrix - _block_size; i++)
		{
			_main_diagonal[i] *= arg;
			_side_diagonal[i] *= arg;
			_upper_side_diagonal[i] *= arg;
		}
		for (size_t i = _order_of_matrix - _block_size; i < _order_of_matrix - 1; i++)
		{
			_main_diagonal[i] *= arg;
			_side_diagonal[i] *= arg;
		}
		_main_diagonal[_order_of_matrix - 1] *= arg;

		return *this;
	}

	DiagonalMatrix operator*(double arg) const noexcept
	{
		DiagonalMatrix result(*this);
		return result *= arg;
	}

	Vector operator*(const Vector& vector) const noexcept
	{
		Vector result(vector);
		for (size_t i = 0; i < _order_of_matrix; i++)
		{
			//double value = 0;

			//value += _main_diagonal[i] * vector[i];

			//value += i > 0 ? _side_diagonal[i - 1] * vector[i - 1] : 0.0;
			//value += i < _order_of_matrix - 1 ? _side_diagonal[i] * vector[i + 1] : 0.0;

			////value += _upper_side_diagonal[i / _block_size] * vector[i + _block_size * (1 - i / _block_size)];
			//value += i >= _block_size ? _upper_side_diagonal[i - _block_size] * vector[i - _block_size] : 0;
			//value += i < _order_of_matrix - _block_size ? _upper_side_diagonal[i] * vector[i + _block_size] : 0;

			//result[i] = value;

			result[i] = multiplyRow(i, vector);
		}

		return result;
	}

	double getElem(int i, int j) const noexcept
	{
		if (i == j)
		{
			return _main_diagonal[i];
		}
		if (i - 1 == j || i + 1 == j)
		{
			return _side_diagonal[i < j ? i : j];
		}
		if (i + _block_size == j || i - _block_size == j)
		{
			return _upper_side_diagonal[i < j ? i : j];
		}
		return 0.0;
	}

	double multiplyRow_Diagonal(int i, const Vector& vector) const noexcept
	{
		double value = 0;
		value += _main_diagonal[i] * vector[i];
		return value;
	}

	//double multiplyRow_UpperTriangular(int i, const Vector& vector) const noexcept
	//{
	//	double value = 0;
	//	value += _main_diagonal[i] * vector[i];
	//	value += i < _order_of_matrix - 1 ? _side_diagonal[i] * vector[i + 1] : 0.0;
	//	value += i < _order_of_matrix - _block_size ? _upper_side_diagonal[i] * vector[i + _block_size] : 0;
	//	return value;
	//}

	//double multiplyRow_UpperTriangular_NoDiagonal(int i, const Vector& vector) const noexcept
	//{
	//	double value = 0;
	//	value += 1 * vector[i];
	//	value += i < _order_of_matrix - 1 ? _side_diagonal[i] * vector[i + 1] : 0.0;
	//	value += i < _order_of_matrix - _block_size ? _upper_side_diagonal[i] * vector[i + _block_size] : 0;
	//	return value;
	//}

	//double multiplyRow_LowerTriangular(int i, const Vector& vector) const noexcept
	//{
	//	double value = 0;
	//	value += _main_diagonal[i] * vector[i];
	//	value += i > 0 ? _side_diagonal[i - 1] * vector[i - 1] : 0.0;
	//	value += i >= _block_size ? _upper_side_diagonal[i - _block_size] * vector[i - _block_size] : 0;
	//	return value;
	//}

	//double multiplyRow_LowerTriangular_NoDiagonal(int i, const Vector& vector) const noexcept
	//{
	//	double value = 0;
	//	value += 1 * vector[i];
	//	value += i > 0 ? _side_diagonal[i - 1] * vector[i - 1] : 0.0;
	//	value += i >= _block_size ? _upper_side_diagonal[i - _block_size] * vector[i - _block_size] : 0;
	//	return value;
	//}

	double multiplyRow(int i, const Vector& vector) const noexcept
	{
		double value = 0;

		value += _main_diagonal[i] * vector[i];

		value += i > 0 ? _side_diagonal[i - 1] * vector[i - 1] : 0.0;
		value += i < _order_of_matrix - 1 ? _side_diagonal[i] * vector[i + 1] : 0.0;

		value += i >= _block_size ? _upper_side_diagonal[i - _block_size] * vector[i - _block_size] : 0;
		value += i < _order_of_matrix - _block_size ? _upper_side_diagonal[i] * vector[i + _block_size] : 0;

		return value;
	}

	void write(std::filesystem::path file_path) const noexcept
	{
		std::ofstream fout(file_path, std::ios::binary | std::ios::trunc);
		fout.write((char*)&_order_of_matrix, sizeof(size_t));
		fout.write((char*)&_block_size, sizeof(size_t));
		const size_t& n = _order_of_matrix;
		const size_t& m = _block_size;
		fout.write((char*)_main_diagonal.data(), sizeof(double) * n);
		fout.write((char*)_side_diagonal.data(), sizeof(double) * (n - 1));
		fout.write((char*)_upper_side_diagonal.data(), sizeof(double) * (n - m));
	}

	void print(size_t n_setw = 1) const noexcept
	{
		for (size_t i = 0; i < _order_of_matrix; i++)
		{
			for (size_t j = 0; j < _order_of_matrix; j++)
			{
				std::cout << std::setw(n_setw * 2 + 1) << std::right << getElem(i, j);
			}
			std::cout << std::string(n_setw - 1, '\n') << std::endl;
		}
		std::cout << std::endl;
	}

	friend DiagonalMatrix make5DiagonalMatrix(size_t Nx, size_t Ny, double u_m, double u_s, double u_us);
	friend DiagonalMatrix make5DiagonalMatrixEquastionPuason(size_t Nx, size_t Ny);
	friend DiagonalMatrix make5DiagonalMatrixEquastionPuason(size_t Nx, size_t Ny, double hx, double hy);
};


DiagonalMatrix make5DiagonalMatrix(size_t Nx, size_t Ny, double diag, double off_diag_x, double off_diag_y)
{
	DiagonalMatrix matrix;

	size_t& n = matrix._order_of_matrix = Nx * Ny;
	size_t& m = matrix._block_size = Nx;

	matrix._main_diagonal.resize(n, diag);
	matrix._side_diagonal.resize(n - 1, off_diag_x);
	for (size_t i = 1; i < Ny; i++)
	{
		matrix._side_diagonal[i * Nx - 1] = 0;
	}
	matrix._upper_side_diagonal.resize(n - m, off_diag_y);

	return matrix;
}

DiagonalMatrix make5DiagonalMatrixEquastionPuason(size_t Nx, size_t Ny)
{
	DiagonalMatrix matrix;

	size_t& n = matrix._order_of_matrix = Nx * Ny;
	size_t& m = matrix._block_size = Nx;

	double Lx = 1;
	double Ly = 1;

	double hx = Lx / (Nx - 1);
	double hy = Ly / (Ny - 1);

	matrix._main_diagonal.resize(n, 2.0 / (hx * hx) + 2.0 / (hy * hy));
	matrix._side_diagonal.resize(n - 1, -1.0 / (hx * hx));
	for (size_t i = 1; i < Ny; i++)
	{
		matrix._side_diagonal[i * Nx - 1] = 0;
	}
	matrix._upper_side_diagonal.resize(n - m, -1.0 / (hy * hy));

	return matrix;
}

DiagonalMatrix make5DiagonalMatrixEquastionPuason(size_t Nx, size_t Ny, double hx, double hy)
{
	DiagonalMatrix matrix;

	size_t& n = matrix._order_of_matrix = Nx * Ny;
	size_t& m = matrix._block_size = Nx;

	matrix._main_diagonal.resize(n, 2.0 * (1.0 / (hx * hx) + 1.0 / (hy * hy)));
	matrix._side_diagonal.resize(n - 1, -1.0 / (hx * hx));
	for (size_t i = 1; i < Ny; i++)
	{
		matrix._side_diagonal[i * Nx - 1] = 0;
	}
	matrix._upper_side_diagonal.resize(n - m, -1.0 / (hy * hy));

	return matrix;
}

template <class MatrixType, class ...>
concept MatrixRule = requires(MatrixType matrix, Vector vector)
{
	{ matrix* vector } -> std::same_as<Vector>;
};