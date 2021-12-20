#include <iostream>
#include "simp_dual.h"

int main()
{
	setlocale(LC_ALL, "RUS");
	simp player_1;
	player_1.simp_method();
	std::cout << std::endl << "двойственной сиплекс матрицы" << std::endl;
	simp_dual player_2;
	player_2.simp_method();
}