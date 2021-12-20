#pragma once
#include <string>
#include <vector>

class simp
{
protected:
	double** mtrx;						//�������
	int m = 0;							//���������� ����������
	int n = 0;						    //���������� �������
	std::vector <std::string> line;		//������� ����� �������
	std::vector <std::string> column;   //������� ����� �������
public:
	simp();
	virtual void print_optimal();
	void print();
	virtual void simplex_iteration();
	void simp_method();
	void conversion_simplex(int& l_pos, int& c_pos);
	bool reference_solution();
};