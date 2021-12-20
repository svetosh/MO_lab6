#include "Simp.h"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <algorithm>
#include <stdexcept>
#include <limits>

namespace fs = std::filesystem;
double** initial_mtrx;

simp::simp()
{
	std::cout << "решениe матричной игры с нулевой суммой." << std::endl
		<< "Введите название файла с матрицей (a.txt) :  ";
	std::string file_name;
	std::getline(std::cin, file_name);
	std::vector <std::string> tmp_mtrx;
	std::vector <int> tmp;
	std::ifstream infile(file_name);
	std::string str;
	while (!infile.eof())
	{
		std::getline(infile, str);
		tmp_mtrx.push_back(str);
		m += 1;
	}
	infile.close();
	n = std::count(tmp_mtrx[0].begin(), tmp_mtrx[0].end(), ' ') - 1;
	double** in_mtrx = new double* [m];
	for (int i = 0; i < m; i++)
	{
		in_mtrx[i] = new double[n];
		for (int h = 0; h <= n; h++)
		{
			if (h == 0)
			{
				tmp.push_back(tmp_mtrx[i].find(' '));
			}
			else
			{
				tmp.push_back(tmp_mtrx[i].find(' ', tmp[tmp.size() - 1] + 1));
			}
		}
		for (int j = 0; j < n; j++)
		{
			in_mtrx[i][j] = std::stod(tmp_mtrx[i].substr(tmp[j], tmp[j + 1]));
		}
		tmp.clear();
	}
	tmp.clear();
	double** _mtrx = new double* [m + 1];
	for (int i = 0; i < (m + 1); i++)
	{
		_mtrx[i] = new double[n + 1];
	}
	for (int i = 0; i < m; i++)
	{
		_mtrx[i][0] = 1;
	}
	for (int i = 1; i < (n + 1); i++)
	{
		_mtrx[m][i] = 1;
	}
	_mtrx[m][0] = 0;
	for (int i = 0; i < m; i++)
	{
		for (int j = 1; j < (n + 1); j++)
		{
			_mtrx[i][j] = in_mtrx[i][j - 1];
		}
	}
	initial_mtrx = in_mtrx;
	mtrx = _mtrx;
	std::string s_tmp = "v_"; // верх таблицы
	for (int i = 0; i < (n + 1); i++)
	{
		if (i == 0)
		{
			line.push_back("S");
		}
		else
		{
			line.push_back(s_tmp + std::to_string(i));
		}
	}
	for (int i = 0; i < (m + 1); i++) // 1й столбец таблицы
	{
		if (i == m)
		{
			column.push_back("Z");
		}
		else
		{
			column.push_back(s_tmp + std::to_string(i + n + 1));
		}
	}
	m += 1;
	n += 1;
}

void simp::print()
{
	std::cout << "Базис";
	for (int i = 0; i < n; i++)
	{
		std::cout << "\t|" << line[i];
	}
	std::cout << std::endl;
	for (int i = 0; i < m; i++)
	{
		std::cout << column[i];
		for (int j = 0; j < n; j++)
		{
			std::string tmp = std::to_string(mtrx[i][j]);
			std::string double_tmp = tmp.substr(0, 5);
			mtrx[i][j] = std::stod(double_tmp);
			std::cout << "\t|" << double_tmp;
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void simp::print_optimal() //функция печати найденного оптимального решения
{
	std::cout << "План оптимален: ";
	double* rez = new double[n - 1];
	std::string s_tmp = "v_";
	for (int i = 0; i < n; i++)
	{
		bool check = false;
		for (int h = 0; h < (m - 1); h++)
		{
			if (column[h] == s_tmp + std::to_string(i + 1))
			{
				rez[i] = mtrx[h][0];
				check = true;
			}
		}
		if (check == false)
		{
			rez[i] = 0;
		}
	}
	std::cout << "Z(";
	for (int i = 0; i < (n - 1); i++)
	{
		if (i == (n - 2))
		{
			std::cout << rez[i] << ")";
		}
		else
		{
			std::cout << rez[i] << " ";
		}
	}
	std::cout << " = " << std::setprecision(5) << (-1) * mtrx[m - 1][0] << std::endl;
	line[0] = "nope";
	std::string tmp = std::to_string((-1) / mtrx[m - 1][0]);
	std::string double_tmp = tmp.substr(0, 7);
	double _rez = std::stod(double_tmp);
	double check = 0;
	std::cout << "Oптимальные смешанные стратегии: (";
	for (int i = 0; i < (n - 1); i++)
	{
		if (i == (n - 2))
		{
			std::cout << rez[i] * _rez << ")";
		}
		else
		{
			std::cout << rez[i] * _rez << " ";
		}
		check += rez[i] * _rez;
	}
	std::cout << std::endl;
	std::vector <int> cost_check;
	int cost = 0;
	for (int i = 0; i < (m - 1); i++)
	{
		int min = std::numeric_limits<int>::max();
		for (int j = 0; j < (n - 1); j++)
		{
			if (initial_mtrx[i][j] < min)
			{
				min = initial_mtrx[i][j];
			}
		}
		cost_check.push_back(min);
	}
	cost = cost_check[0];
	for (int& h : cost_check)
	{
		if (h > cost)
		{
			cost = h;
		}
	}
	std::cout << "Верхняя стоимость игры: " << cost << std::endl;;
	cost = 0;
	cost_check.clear();
	for (int i = 0; i < (n - 1); i++)
	{
		int max = std::numeric_limits<int>::min();
		for (int j = 0; j < (m - 1); j++)
		{
			if (initial_mtrx[j][i] > max)
			{
				max = initial_mtrx[j][i];
			}
		}
		cost_check.push_back(max);
	}
	cost = cost_check[0];
	for (int& h : cost_check)
	{
		if (h < cost)
		{
			cost = h;
		}
	}
	std::cout << "Нижняя стоимость игры: " << cost << std::endl;
	std::cout << "Стоимость игры: " << _rez << std::endl;
}

void simp::conversion_simplex(int& l_pos, int& c_pos) //функция симплекс пересчёта
{
	std::swap(line[c_pos], column[l_pos]); //меняем необходимые переменные
	double** result_matrix = new double* [m]; //матрица-результат
	for (int i = 0; i < m; i++) //заполняем матрицу-результат по правилaм
	{
		result_matrix[i] = new double[n];
	}
	result_matrix[l_pos][c_pos] = (1 / mtrx[l_pos][c_pos]);
	for (int i = 0; i < n; i++)
	{
		if (i != c_pos)
		{
			result_matrix[l_pos][i] = mtrx[l_pos][i] / mtrx[l_pos][c_pos];
		}
	}
	for (int i = 0; i < m; i++)
	{
		if (i != l_pos)
		{
			result_matrix[i][c_pos] = -1 * mtrx[i][c_pos] / mtrx[l_pos][c_pos];
		}
	}
	for (int i = 0; i < m; i++)
	{
		if (i != l_pos)
		{
			for (int j = 0; j < n; j++)
			{
				if (j != c_pos)
				{
					result_matrix[i][j] = mtrx[i][j] - (mtrx[i][c_pos] * mtrx[l_pos][j] /
						mtrx[l_pos][c_pos]);
				}
			}
		}
	}
	for (int i = 0; i < m; i++)
	{
		delete[] mtrx[i];
	}
	delete[] mtrx;
	mtrx = result_matrix;
}

bool simp::reference_solution() //функция поиска опорного решения
{
	int c_pos; //нахождение разрешающего столбца
	int l_pos; //нахождение разрешающей строки
	bool flag_rez = false;
	int check = 0;
	while ((flag_rez != true) && (check != (m - 1))) //проверка
	{
		if (mtrx[check][0] < 0)
		{
			l_pos = check;
			flag_rez = true;
		}
		check += 1;
	}
	if (flag_rez == true) //если проверка не пройдено, то выполняется поиск
	{
		for (int j = 1; j < n; j++)
		{
			if (mtrx[l_pos][j] < 0)
			{
				c_pos = j;
				conversion_simplex(l_pos, c_pos);
				return true;
			}
		}
	}
	return false;
}

void simp::simplex_iteration()
{
	int c_pos;						//нахождение разрешающего столбца
	int l_pos;						//нахождение разрешающей строки
	bool flag = false;				//флаг для проверки оптимальности решения
	for (int i = 1; i < n; i++)
	{
		if (mtrx[m - 1][i] > 0)
		{
			flag = true;
		}
	}
	if (flag == false)
	{
		print_optimal();
	}
	else
	{
		c_pos = 1; //нахождение разрешающего столбца
		double max = mtrx[m - 1][1];
		for (int i = 2; i < n; i++)
		{
			if (mtrx[m - 1][i] > max)
			{
				max = mtrx[m - 1][i];
				c_pos = i;
			}
		}
		l_pos = 0; //нахождение разрешающей строки
		double min = std::numeric_limits<double>::max();
		for (int i = 0; i < (m - 1); i++)
		{
			if (((mtrx[i][0] / mtrx[i][c_pos]) >= 0) && ((mtrx[i][0] / mtrx[i][c_pos])
				< min) && (mtrx[i][c_pos] > 0))
			{
				min = mtrx[i][0] / mtrx[i][c_pos];
				l_pos = i;
			}
		}
		conversion_simplex(l_pos, c_pos);
	}
}

void simp::simp_method()
{
	do
	{
		print();
	} while (reference_solution());		//поиск опорного решения
	simplex_iteration();				//поиск оптимального решения
	while (line[0] != "nope")
	{
		print();
		simplex_iteration();
	}
	for (int i = 0; i < m; i++)
	{
		delete[] mtrx[i];
	}
	delete[] mtrx;
}