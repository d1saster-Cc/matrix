#include "matrix.h"
#include <iostream>
#include <fstream>

int main() {
	vector<vector<double>> s = { {2, 5, 7},
								{4, 3, 4},
								{7, 4, -3} };

	vector<vector<double>> ss = {   {1, 2, 2},
									{0, 4, 2},
									{0, 0, 1} };


	vector<double> v1 = { 1, 3, 4, 5, 11};
	vector<double> v2 = { 1, 1, 2};
	vector<double> v11 = { 1, 2, 3 ,4, 5, 6, 7,8,9,10 };
	vector<double> vt;
	Matrix s2 = ss;
	/*Matrix t(4, 4);
	std::ifstream out;          // поток для записи
	out.open("mtr.txt"); // окрываем файл для записи
	if (out.is_open())
	{
		out >> vt;
	}

	cout << vt;*/

	//writebinary("test.bin", s2);
	cout << readbinary("test.bin");
	return 0;
}