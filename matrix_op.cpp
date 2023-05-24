#include "matrix.h"

Matrix& Matrix::operator+=(const Matrix& rhs) {
	try {
		if (row != rhs.row || column != rhs.column) {
			throw "Size error";
		}
	}
	catch (const char* exception) // обработчик исключений типа const char*
	{
		cerr << "Error: " << exception << '\n'; //стандартный поток для исключений
	}

	for (int i = 0; i < rhs.row; i++)
	{
		for (int j = 0; j < rhs.column; j++)
		{
			this->m[i][j] += rhs.m[i][j];
		}
	}
	return *this;
}

Matrix& Matrix::operator-=(const Matrix& rhs) {
	try {
		if (row != rhs.row || column != rhs.column) {
			throw "Size error";
		}
	}
	catch (const char* exception) // обработчик исключений типа const char*
	{
		cerr << "Error: " << exception << '\n'; //стандартный поток для исключений
	}

	for (int i = 0; i < rhs.row; i++)
	{
		for (int j = 0; j < rhs.column; j++)
		{
			this->m[i][j] -= rhs.m[i][j];
		}
	}
	return *this;
}

Matrix& Matrix::operator*=(const Matrix& rhs) {
	try {
		if (this->column != rhs.row) {
			throw "Size error";
		}
	}
	catch (const char* exception) // обработчик исключений типа const char*
	{
		cerr << "Error: " << exception << '\n'; //стандартный поток для исключений
	}
	vector<vector<double>> res;
	res.resize(this->row, vector<double>(rhs.column));
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < rhs.column; j++)
		{
			res[i][j] = 0;
			for (int k = 0; k < this->column; k++) {
				res[i][j] += this->m[i][k] * rhs.m[k][j];
			}
		}
	}
	*this = res;
	return *this;
}

Matrix& Matrix::operator*=(const double& rhs) {
	for (int i = 0; i < this->row; i++)
	{
		for (int j = 0; j < this->column; j++)
		{
			this->m[i][j] *= rhs;
		}
	}
	return *this;
}

Matrix& Matrix::operator/=(const double& rhs) {
	for (int i = 0; i < this->row; i++)
	{
		for (int j = 0; j < this->column; j++)
		{
			this->m[i][j] /= rhs;
		}
	}
	return *this;
}


const Matrix Matrix::operator+ (const Matrix& rhs) {
	return Matrix(*this) += rhs;
}

const Matrix Matrix::operator- (const Matrix& rhs) {
	return Matrix(*this) -= rhs;
}

const Matrix Matrix::operator* (const Matrix& rhs) {
	return Matrix(*this) *= rhs;
}

const Matrix Matrix::operator* (const double& rhs) {
	return Matrix(*this) *= rhs;
}

const Matrix Matrix::operator/ (const double& rhs) {
	return Matrix(*this) /= rhs;
}


void Matrix::ShowMatrix(ostream& strm) const {
	size_t max = 0;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			max = getLendth(m[i][j]) > max ? getLendth(m[i][j]) : max;
		}
	}

	for (int i = 0; i < row; i++)
	{
		strm << endl;
		strm << "|";
		for (int j = 0; j < column; j++)
		{
			size_t lenth = getLendth(m[i][j]); //текущая длина
			strm << std::setfill(' ') << std::setw(max - lenth) << "" << m[i][j] << "  ";
		}
		strm << "|";
	}
}

//Для векторов




Matrix operator+ (const vector<double>& lhs, const vector<double>& rhs) {
	Matrix s1 = lhs;
	Matrix s2 = rhs;
	return s1 + s2;
}

Matrix operator- (const vector<double>& lhs, const vector<double>& rhs) {
	Matrix s1 = lhs;
	Matrix s2 = rhs;
	return s1 - s2;
}

Matrix operator* (const vector<double>& lhs, const double& rhs) {
	Matrix s1 = lhs;
	return s1 * rhs;
}

Matrix operator* (const vector<double>& lhs, const Matrix& rhs) {
	Matrix s1 = lhs;
	return s1 * rhs;
}

Matrix operator* (Matrix& lhs, const vector<double>& rhs) {
	Matrix s1 = rhs;
	return lhs * s1;
}

Matrix operator+ (const vector<double>& lhs, const Matrix& rhs) {
	Matrix s1 = lhs;
	return s1 + rhs;
}

Matrix operator- (const vector<double>& lhs, const Matrix& rhs) {
	Matrix s1 = lhs;
	return s1 - rhs;
}

//adamar

Matrix Adamar(const Matrix& m1, const Matrix& m2) {
	try {
		if (m1.row != m2.row || m1.column != m2.column) {
			throw "Size error";
		}
	}
	catch (const char* exception) // обработчик исключений типа const char*
	{
		cerr << "Error: " << exception << '\n'; //стандартный поток для исключений
	}
	vector<vector<double>> res;
	res.resize(m1.row, vector<double>(m1.column));
	for (int i = 0; i < m2.row; i++)
	{
		for (int j = 0; j < m2.column; j++)
		{
			res[i][j] = m1.m[i][j] * m2.m[i][j];
		}
	}
	return res;
}


bool operator== (const Matrix& m1, const Matrix& m2) {
	if (m1.row != m2.row) return false;
	else if (m1.column != m2.column) return false;
	for (int i = 0; i < m1.row; i++)
	{
		for (int j = 0; j < m1.column; j++)
		{
			if (m1.m[i][j] != m2.m[i][j]) return false;
		}
	}
	return true;
}