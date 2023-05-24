#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
#include <sstream>

using namespace std;

template<class T>
int getLendth(T num)
{
	//std::cout.setf(std::ios::fixed);
	stringstream s_stream;
	string s_string;
	s_stream << num;
	s_stream >> s_string;
	return s_string.size();
}

class Matrix {

public:
	Matrix();

	Matrix(int row, int column);

	Matrix(vector<double> s);

	Matrix(vector<vector<double>> s);

	Matrix(const Matrix &matrix);

	void ShowMatrix(ostream& strm) const;
	friend Matrix Adamar(const Matrix& m1, const Matrix& m2);
	friend double trace(const Matrix& matrix);
	friend double gauss_det(Matrix m1);
	friend double Frobenius(const Matrix& matr);
	friend int Rank(Matrix matrix);
	friend Matrix Inverse(const Matrix& matr);
	friend Matrix transpose_alg_dop(const Matrix& matr);
	friend Matrix make_kv(vector<double> s);
	friend Matrix Transpose(const Matrix& matr);
	friend bool operator== (const Matrix& m1, const Matrix& m2);
	friend ostream& operator<<(ostream& out, const Matrix& matrix);
	friend istream& operator>> (istream& in, Matrix& matrix);
	friend void writebinary(const char* filename, const Matrix& matr);
	Matrix& operator+=(const Matrix& rhs);
	Matrix& operator-=(const Matrix& rhs);
	Matrix& operator*=(const Matrix& rhs);
	Matrix& operator*=(const double& rhs);
	Matrix& operator/=(const double& rhs);
	const Matrix operator+(const Matrix& rhs);
	const Matrix operator-(const Matrix& rhs);
	const Matrix operator*(const Matrix& rhs);
	const Matrix operator*(const double& rhs);
	const Matrix operator/(const double& rhs);

protected:
	vector<vector<double>> m;
	int row;
	int column;
};

class identity_matrix : public Matrix {
public:
	identity_matrix();
	identity_matrix(int x);
};

class diagonal_matrix : public Matrix {
public:
	diagonal_matrix();
	diagonal_matrix(int x, int y);
	diagonal_matrix(vector<double> v);
};

class simm_matrix : public Matrix {
public:
	simm_matrix(vector<vector<double>> s);
};

class UTmatrix :public Matrix {
public:
	UTmatrix(size_t n, vector<vector<double>> val);
};

class LTmatrix :public Matrix {
public:
	LTmatrix(size_t n, vector<vector<double>> val);
};

ostream& operator<<(ostream& out, const Matrix& matrix);
Matrix operator+ (const vector<double>& lhs, const vector<double>& rhs);
Matrix operator- (const vector<double>& lhs, const vector<double>& rhs);
Matrix operator* (const vector<double>& lhs, const Matrix& rhs);
Matrix operator* (const vector<double>& lhs, const double& rhs);
Matrix operator* (Matrix& lhs, const vector<double>& rhs);
Matrix operator+ (const vector<double>& lhs, const Matrix& rhs);
Matrix operator- (const vector<double>& lhs, const Matrix& rhs);

double Scalar(const vector<double>& v1, const vector<double>& v2);
double Euclid(const vector<double>& v);
double Chebishev(const vector<double>& v);
double angle(const vector<double>& v1, const vector<double>& v2, const char* c = "Cos");
Matrix make_kv(vector<double> s);


ostream& operator<<(ostream& out, const vector<double>& v);
istream& operator>> (istream& in, vector<double>& v);

void writeVecToBin(vector<double> v, const char* filename);
void readVecFromBin(vector<double>& v, const char* filename);


Matrix readbinary(const char* filename);