#define _CRT_SECURE_NO_WARNINGS
#include "matrix.h"
#include <fstream>      //Для работы с файлом
#include <iostream>
#include <iterator>



ostream& operator<<(ostream& out, const Matrix& matrix)
{
	for (int i = 0; i < matrix.row; i++)
	{
		for (int j = 0; j < matrix.column; j++)
		{
			out << matrix.m[i][j] << " ";
		}
		out << "\n";
	};
	return out;
}


istream& operator>> (istream& in, Matrix& matrix) {
	for (int i = 0; i < matrix.row; i++)
	{
		for (int j = 0; j < matrix.column; j++)
		{
			in >> matrix.m[i][j];
		}
	}
	return in;
}


ostream& operator<<(ostream& out, const vector<double>& v) //ф-ция для вывода матрицы
{
	for (int i = 0; i < v.size(); i++) {
		out << v[i] << " ";
	}
	return out;
}

istream& operator>> (istream& in, vector<double>& v) {

	for (int n; in >> n; )
	{
		v.push_back(n);
	}

	return in;
}

void writeVecToBin(vector<double> v, const char* filename) {
	std::ofstream ofs(filename, std::ios::binary);
	//ofs >> std::noskipws;
	std::copy(v.begin(), v.end(), std::ostream_iterator<double>(ofs));
}

void readVecFromBin(vector<double>& v, const char* filename) {
	std::ifstream out(filename, std::ios::binary);
	//out.unsetf(std::ios::skipws);
	out >> std::noskipws;
	std::copy(std::istream_iterator<double>(out), std::istream_iterator<double>(), std::back_inserter(v));
}

void writebinary(const char* filename, const Matrix& matr) {
	FILE* f;
	f = fopen(filename, "wb");

	char c, s;
	c = '\n';
	s = ' ';
	for (int i = 0; i < matr.row; i++) {
		for (int j = 0; j < matr.column; j++) {
			fwrite(&matr.m[i][j], 1, sizeof(double), f);
			if (j != matr.column - 1) fwrite(&s, 1, sizeof(char), f);
		}
		fwrite(&c, 1, sizeof(char), f);
	}

	fclose(f);
}

Matrix readbinary(const char* filename) {
	FILE* f;
	f = fopen(filename, "rb");
	if (f == NULL) exit(1);
	double ftmp;
	char ctmp;

	vector<vector<double>> vvtmp;
	int n = 0;
	int m = 0;
	int k = 0;
	vector<double> vtmp;
	while (!feof(f)) {

		fread(&ftmp, sizeof(double), 1, f);
		fread(&ctmp, sizeof(char), 1, f);
		k++;
		vtmp.push_back(ftmp);
		//cout << ftmp;
		if (ctmp == '\n' || feof(f)) {

			if (m == 0) m = k;
			if (m != k && !feof(f)) exit(1);
			if (!feof(f)) k = 0;
			n++;
			vvtmp.push_back(vtmp);
			vtmp.clear();
		}
	}
	n--;
	vvtmp.pop_back();
	return Matrix(vvtmp);

}

