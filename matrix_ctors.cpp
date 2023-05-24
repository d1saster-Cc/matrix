#include "matrix.h"

Matrix::Matrix() : row(0), column(0) {}

Matrix::Matrix(int row, int column) : row(row), column(column)
{
	m.resize(row, vector<double>(column));
}

Matrix::Matrix(vector<double> s) : row(1), column(s.size())
{
	m.resize(row, vector<double>(column));
	m.at(0) = s;
}


Matrix::Matrix(vector<vector<double>> s) : row(s.size()), column(s[0].size())
{
	m.resize(row, vector<double>(column));
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			m[i][j] = s[i][j];
		}
	}
}

Matrix::Matrix(const Matrix &matrix) : row(matrix.row), column(matrix.column) {
	m.resize(row, vector<double>(column));
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			m[i][j] = matrix.m[i][j];
		}
	}
}

//единична€
identity_matrix::identity_matrix() : Matrix(2, 2) {
	m[0][0] = 1;
	m[0][1] = 0;
	m[1][0] = 0;
	m[1][1] = 1;
}

identity_matrix::identity_matrix(int x) : Matrix(x, x) {
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			if (i == j) this->m[i][j] = 1;
			else m[i][j] = 0;
		}
	}
}

//диагональна€
diagonal_matrix::diagonal_matrix() : Matrix(2, 2) {
	m[0][0] = 1;
	m[0][1] = 0;
	m[1][0] = 0;
	m[1][1] = 1;
}

diagonal_matrix::diagonal_matrix(int x, int y) : Matrix(y, y) {
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			if (i == j) this->m[i][j] = x;
			else m[i][j] = 0;
		}
	}
}
diagonal_matrix::diagonal_matrix(vector<double> v) : Matrix(v.size(), v.size()) {
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			if (i == j) this->m[i][j] = v[i];
			else m[i][j] = 0;
		}
	}
}

//симметрична€
simm_matrix::simm_matrix(vector<vector<double>> s) : Matrix(s) {
	try {
		if (!(*this == Transpose(*this))) throw "This is not simm matrix!";
	}
	catch (const char* exception) // обработчик исключений типа const char*
	{
		cerr << "Error: " << exception << '\n'; //стандартный поток дл€ исключений
	}
}

//верхн€€ и нижн€€ треуг

UTmatrix::UTmatrix(size_t n, vector<vector<double>> val) :Matrix(n, n) {
	try {
		if (size(val) != n) throw "This is not UT matrix!";

		for (int i = 0; i < n; i++) {
			if (size(val[i]) != n) throw "This is not UT matrix!";
		}

		for (int i = 0; i < n; i++) {
			for (int j = 0; j <= i; j++) {
				if (i != j && val[i][j] != 0) throw "NotUpperTriangleMatrix";
				this->m[j][i] = val[j][i];
			}
		}
	}
	catch (const char* exception) // обработчик исключений типа const char*
	{
		cerr << "Error: " << exception << '\n'; //стандартный поток дл€ исключений
	}
}



LTmatrix::LTmatrix(size_t n, vector<vector<double>> val) :Matrix(n, n) {
	try {
		if (size(val) != n) throw "This is not LT matrix!";
		for (int i = 0; i < n; i++) {
			if (size(val[i]) != n) throw "This is not LT matrix!";
		}

		for (int i = 0; i < n; i++) {
			for (int j = 0; j <= i; j++) {

				if (i != j && val[j][i] != 0) {
					throw "NotLowerTriangleMatrixException";
				}
				this->m[i][j] = val[i][j];
			}
		}
	}
	catch (const char* exception) // обработчик исключений типа const char*
	{
		cerr << "Error: " << exception << '\n'; //стандартный поток дл€ исключений
	}
}