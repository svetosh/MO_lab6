#include "Simp_dual.h"
#include <iostream>
#include <iomanip>

simp_dual::simp_dual()
{
	double** _mtrx = new double* [n];
	for (int i = 0; i < n; i++)
	{
		_mtrx[i] = new double[m];
	}
	for (int i = 0; i < (n - 1); i++)
	{
		_mtrx[i][0] = -1;
	}
	for (int i = 1; i < m; i++)
	{
		_mtrx[n - 1][i] = -1;
	}
	_mtrx[n - 1][0] = 0;
	for (int i = 0; i < (n - 1); i++)
	{
		for (int j = 1; j < m; j++)
		{
			if (mtrx[j - 1][i + 1] == 0)
			{
				_mtrx[i][j] = mtrx[j - 1][i + 1];
			}
			else
			{
				_mtrx[i][j] = -1 * (mtrx[j - 1][i + 1]);
			}
		}
	}
	mtrx = _mtrx;
	line.clear();
	column.clear();
	int tmp = n;
	n = m;
	m = tmp;
	std::string s_tmp = "u_";
	for (int i = 0; i < n; i++)
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
	for (int i = 0; i < m; i++)
	{
		if (i == (m - 1))
		{
			column.push_back("W");
		}
		else
		{
			column.push_back(s_tmp + std::to_string(i + n));
		}
	}
}

void simp_dual::print_optimal()
{
	std::cout << "Ваш план оптимален: ";
	double* rez = new double[n - 1];
	std::string s_tmp = "u_";
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
	std::cout << "W(";
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
	std::cout << " = " << std::setprecision(7) << mtrx[m - 1][0] << std::endl;
	line[0] = "nope";
	std::string tmp = std::to_string(1 / mtrx[m - 1][0]);
	std::string double_tmp = tmp.substr(0, 7);
	double _rez = std::stod(double_tmp);
	double check = 0;
	std::cout << "Ваши оптимальные смешанные стратегии: (";
	for (int i = 0; i < (n - 1); i++)
	{
		if (i == (n - 2))
		{
			std::cout << rez[i] * _rez << ")";
		}
		else
		{
			std::cout << rez[i] * _rez << ", ";
		}
		check += rez[i] * _rez;
	}
	std::cout << std::endl;
}