#pragma once
#include <string>
#include <vector>

class simp
{
protected:
	double** mtrx;						//матрица
	int m = 0;							//количество переменных
	int n = 0;						    //количество условий
	std::vector <std::string> line;		//верхняя шапка таблицы
	std::vector <std::string> column;   //боковая шапка таблицы
public:
	simp();
	virtual void print_optimal();
	void print();
	virtual void simplex_iteration();
	void simp_method();
	void conversion_simplex(int& l_pos, int& c_pos);
	bool reference_solution();
};