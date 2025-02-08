#include "hw1.h"

#include <iostream>
#include <random>

using std::cout;

Matrix zeros(size_t n, size_t m)
{
	Matrix matrix(n, vector<double>(m, 0));
	return matrix;
}

Matrix ones(size_t n, size_t m)
{
	Matrix matrix(n, vector<double>(m, 1));
	return matrix;
}

Matrix random(size_t n, size_t m, double min, double max)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> dist(min, max);
	Matrix matrix(n, vector<double>(m));
	
	for (int i = 0; i < matrix.size(); i++)
		for (int j = 0; j < matrix[i].size(); j++) {
			double rand = dist(mt);
			matrix[i][j] = rand;
		}
	return matrix;
}

void show(const Matrix& matrix)
{
	for (int i = 0; i < matrix.size(); i++)
		for (int j = 0; j < matrix[i].size(); j++)
			cout << matrix[i][j];
	return;
}

Matrix mutiply(const Matrix& matrix, double c)
{
	Matrix matrix_new(matrix);
	for (int i = 0; i < matrix.size(); i++)
		for (int j = 0; j < matrix[i].size(); j++)
			matrix_new[i][j] = matrix[i][j] * c;
	return matrix_new;
}

Matrix mutiply(const Matrix& matrix1, const Matrix& matrix2)
{
	Matrix matrix(matrix1.size(), vector<double>(matrix2[0].size()));
	for (int i = 0; i < matrix.size(); i++)
	{
		vector<double> array(matrix[i].size(), 0);
		for (int j = 0; j < matrix1[i].size(); j++) {
			for(int k = 0; k < matrix[i].size(); k++) {
				array[k] = matrix1[i][j] * matrix2[j][k];

			}
		}
		matrix[i] = array;
	}
	return matrix;
}

Matrix sum(const Matrix& matrix, double c)
{
	Matrix matrix_new(matrix);
	for (int i = 0; i < matrix.size(); i++)
		for (int j = 0; j < matrix[i].size(); j++)
			matrix_new[i][j] = matrix[i][j] + c;
	return matrix_new;
}

Matrix sum(const Matrix& matrix1, const Matrix& matrix2) 
{
	Matrix matrix_new(matrix1);
	for (int i = 0; i < matrix1.size(); i++)
		for (int j = 0; j < matrix1[i].size(); j++)
			matrix_new[i][j] = matrix1[i][j] + matrix2[i][j];
	return matrix_new;
}

Matrix transpose(const Matrix& matrix)
{
	Matrix matrix_new(matrix[0].size(), vector<double>(matrix.size()));
	for (int i = 0; i < matrix_new.size(); i++)
		for (int j = 0; j < matrix_new[i].size(); i++) {
			matrix_new[i][j] = matrix[j][i];
		}
	return matrix_new;
}

Matrix minor(const Matrix& matrix, size_t n, size_t m);
Matrix inverse(const Matrix& matrix);
Matrix concatenate(const Matrix& matrix1, const Matrix& matrix2, int axis=0);
Matrix ero_swap(const Matrix& matrix, size_t r1, size_t r2);
Matrix ero_multiply(const Matrix& matrix, size_t r, double c);
Matrix ero_sum(const Matrix& matrix, size_t r1, double c, size_t r2);
Matrix upper_triangular(const Matrix& matrix);

double determinant(const Matrix& matrix);
