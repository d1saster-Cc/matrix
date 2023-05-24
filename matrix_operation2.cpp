#include "matrix.h"
#include "algorithm"
#include <cmath>

double trace(const Matrix& matrix) {
	double res = 0;
	for (int i = 0; i < matrix.row; i++)
	{
		for (int j = 0; j < matrix.column; j++)
		{
			if (i == j) res += matrix.m[i][j];
		}
	}
	return res;
}

double gauss_det(Matrix m1) {
	const double EPS = 1E-9;
	double det = 1;

	for (int i = 0; i < m1.row; ++i) {
		int k = i;
		for (int j = i + 1; j < m1.row; ++j)
			if (abs(m1.m[j][i]) > abs(m1.m[k][i]))
				k = j;
		if (abs(m1.m[k][i]) < EPS) {
			det = 0;
			break;
		}
		swap(m1.m[i], m1.m[k]);
		if (i != k)
			det = -det;
		det *= m1.m[i][i];
		for (int j = i + 1; j < m1.row; ++j)
			m1.m[i][j] /= m1.m[i][i];
		for (int j = 0; j < m1.row; ++j)
			if (j != i && abs(m1.m[j][i]) > EPS)
				for (int k = i + 1; k < m1.row; ++k)
					m1.m[j][k] -= m1.m[i][k] * m1.m[j][i];
	}
	return det;
}

double Scalar(const vector<double>& v1, const vector<double>& v2) {
	try {
		if (v1.size() != v2.size()) {
			throw "Size error";
		}
		double res = 0;
		for (int i = 0; i < v1.size(); i++) {
			res += v1[i] * v2[i];
		}
		return res;
	}
	catch (const char* exception) // обработчик исключений типа const char*
	{
		cerr << "Error: " << exception << '\n'; //стандартный поток для исключений
	}
}



double Euclid(const vector<double>& v) {
	double res = 0;
	for (int i = 0; i < v.size(); i++) {
		res += v[i]* v[i];
	}
	return sqrt(res);
}

double Chebishev(const vector<double>& v) {
	return *max_element(v.begin(), v.end());
}



double Frobenius(const Matrix& matrix) {
	double res = 0;
	for (int i = 0; i < matrix.row; i++)
	{
		for (int j = 0; j < matrix.column; j++)
		{
			res += matrix.m[i][j] * matrix.m[i][j];
		}
	}
	return sqrt(res);
}

double angle(const vector<double>& v1, const vector<double>& v2, const char* c) {
	double res = Scalar(v1, v2) / (Euclid(v1) * Euclid(v2));
	try {
		if (c == "Cos") return res;
		else if (c == "Angle") return acos(res);
		else throw "Wrong choice";
	}
	catch (const char* exception) // обработчик исключений типа const char*
	{
		cerr << "Error: " << exception << '\n'; //стандартный поток для исключений
	}
}

int Rank(Matrix matrix) {
	const double EPS = 1E-9;

	int rank = max(matrix.row, matrix.column);
	vector<char> line_used(matrix.row);
	for (int i = 0; i < matrix.column; ++i) {
		int j;
		for (j = 0; j < matrix.row; ++j)
			if (!line_used[j] && abs(matrix.m[j][i]) > EPS)
				break;
		if (j == matrix.row)
			--rank;
		else {
			line_used[j] = true;
			for (int p = i + 1; p < matrix.column; ++p)
				matrix.m[j][p] /= matrix.m[j][i];
			for (int k = 0; k < matrix.row; ++k)
				if (k != j && abs(matrix.m[k][i]) > EPS)
					for (int p = i + 1; p < matrix.column; ++p)
						matrix.m[k][p] -= matrix.m[j][p] * matrix.m[k][i];
		}
	}
	return rank;
}

Matrix make_kv(vector<double> s) {
	double wtf;
	int raz = sqrt(s.size());
	if (modf(raz, &wtf) == 0) {
		Matrix res(raz, raz);
		int c = 0;
		for (int i = 0; i < raz; i++)
		{
			for (int j = 0; j < raz; j++)
			{
				res.m[i][j] = s[c];
				c++;
			}
		}
		return res;
	}
	else return identity_matrix();
}


Matrix transpose_alg_dop(const Matrix& matr) {
	try {
		if (matr.row != matr.column) throw "Bad size";
	}
	catch (const char* exception) // обработчик исключений типа const char*
	{
		cerr << "Error: " << exception << '\n'; //стандартный поток для исключений
	}



	if (matr.row == 2) {
		Matrix res2 = matr;
		swap(res2.m[0][0], res2.m[1][1]);
		res2.m[0][1] *= -1;
		res2.m[1][0] *= -1;
		return res2;
	}

	Matrix res(matr.row, matr.column);
	vector<double> l;
	for (int i = 0; i < matr.row; i++)
	{
		for (int j = 0; j < matr.column; j++)
		{
			for (int s = 0; s < matr.row; s++)
			{
				for (int p = 0; p < matr.column; p++)
				{
					if (s != i && p != j) l.push_back(matr.m[s][p]);
				}
			}
			res.m[j][i] = pow(-1, i+j)*gauss_det(make_kv(l));
			l.clear();
		}
	}
	return res;
}


Matrix Inverse(const Matrix& matr) {
	try {
		if (matr.row != matr.column) throw "Bad size";
		else if (gauss_det(matr) == 0) throw "Det is 0";
	}
	catch (const char* exception) // обработчик исключений типа const char*
	{
		cerr << "Error: " << exception << '\n'; //стандартный поток для исключений
	}
	return transpose_alg_dop(matr) / gauss_det(matr);
}

Matrix Transpose(const Matrix& matr) {
	Matrix res(matr.column, matr.row);

	for (int i = 0; i < matr.row; i++)
	{
		for (int j = 0; j < matr.column; j++)
		{
			res.m[j][i] = matr.m[i][j];
		}
	}
	return res;
}