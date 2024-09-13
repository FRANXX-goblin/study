#pragma once
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;
#define PI 3.1415926
#define max_value 2
#define min_value -1
#define crossover_rate 0.75
#define mutation_rate 0.05

class Bin
{
public:
	Bin(int bin_num, int bin_capacity) :bin_capacity(bin_capacity), bin_num(bin_num)
	{
		bin=new int*[bin_num];
		for (int i = 0; i < bin_num; i++)
		{
			bin[i]=new int[bin_capacity];
		}
		for (int i = 0; i < bin_num; i++) {
			for (int j = 0; j < bin_capacity; j++) {
				int n = rand() % 100 + 1;
				if (n <= 50) 
				{
					bin[i][j] = 1;
				}
				else 
				{
					bin[i][j] = 0;
				}
			}
		}

		toTen = new int[bin_num];
		x = new double[bin_num];
		fitness = new double[bin_num];
		selected_rate = new double[bin_num];
		turntable = new double[bin_num];
		update_turntable();
	}
	~Bin()
	{
	}

public://以下为获取函数
	int capacity() const
	{
		return bin_capacity;
	}
	int size() const
	{
		return bin_num;
	}
	int get(int x, int y)
	{
		return bin[x][y];
	}
	int* get(int bin_index)//返回指定的箱子指针
	{
		return bin[bin_index];
	}


public://以下为打印函数
	void print_bin() 
	{
		for (int i = 0; i < bin_num; i++)
		{
			for (int j = 0; j < bin_capacity; j++)
			{
				cout << bin[i][j];
			}
			cout << endl;
		}
	}
	void print_toTen()
	{
		for (int i = 0; i < bin_num; i++)
		{
			cout << toTen[i] << " ";
		}
		cout << endl;
	}
	void print_x()
	{
		cout<<fixed<<setprecision(6); // 设置精度为6位小数
		for (int i = 0; i < bin_num; i++)
		{
			cout << x[i] << " ";
		}
		cout << endl;
	}
	void print_fitness()
	{
		cout<<fixed<<setprecision(6); // 设置精度为6位小数
		for (int i = 0; i < bin_num; i++)
		{
			cout << fitness[i] << " ";
		}
		cout << endl;
	}
	void print_max_fitness()
	{
		cout << max_fitness()<<endl;
	}

public://以下为更新函数
	void update_toTen()
	{
		for (int i = 0; i < bin_num; i++)
		{
			toTen[i] = two2ten(i);
		}
	}
	void update_x()
	{
		update_toTen();
		for (int i = 0; i < bin_num; i++)
		{
			x[i] = (toTen[i] * (max_value - min_value) / (pow(2, bin_capacity) - 1)) + min_value;
		}
	}
	void update_fitness() 
	{
		update_x();
		for (int i = 0; i < bin_num; i++)
		{
			fitness[i] = x[i] * sin(10 * PI * x[i]) + 2;
		}
	}
	double sum_fitness() 
	{
		double sum_fitness = 0;
		for (int i = 0; i < bin_num; i++)
		{
			sum_fitness += fitness[i];
		}
		return sum_fitness;
	}
	void update_selected_rate()
	{
		update_fitness();
		for (int i = 0; i < bin_num; i++)
		{
			selected_rate[i] = fitness[i] / sum_fitness();
		}
	}
	void update_turntable() 
	{
		update_selected_rate();
		turntable[0] = selected_rate[0];
		for (int i = 1; i < bin_num - 1; i++)
		{
			turntable[i] = selected_rate[i] + turntable[i - 1];
		}
		turntable[bin_num - 1] = 1;
	}


public://以下为辅助函数
	int operator() (int bin_index, int index)
	{ 
		return bin[bin_index][index];
	}
	int two2ten(int bin_index)
	{
		int ten = 0;
		for (int i = 0; i < bin_capacity; i++)
		{
			int temp = 0;
			if (bin[bin_index][i] == 1)
			{
				temp = pow(2, bin_capacity - i - 1);
			}
			ten += temp;
		}
		return ten;
	}
	void swap(int bin_index1, int bin_index2, int index) //交换两个箱子里的物品
	{
		int temp = bin[bin_index1][index];
		bin[bin_index1][index] = bin[bin_index2][index];
		bin[bin_index2][index] = temp;
	}
	double max_fitness()
	{
		double max_fit = fitness[0];
		for (int i = 1; i < bin_num; i++)
		{
			if (fitness[i] > max_fit)
			{
				max_fit = fitness[i];
			}
		}
		return max_fit;
	}
public://以下为遗传算法相关函数
	int selection() 
	{
		double rand_num = (double)(rand() % 100 + 1) / 100;
		for (int i = 0; i < bin_num; i++)
		{
			if (rand_num <= turntable[i])
			{
				if (i < bin_num)
					return i;
			}
		}
	}
	void crossover()
	{
		int father1_index = selection();
		int father2_index = selection();
		if (rand() % 100 < crossover_rate * 100)
		{
			int beg_cross_index = rand() % 100;
			for (int i = beg_cross_index; i < bin_capacity; i++) 
			{
				swap(father1_index, father2_index, i);
			}
		}

	}
	void mutation() 
	{
		for (int i = 0; i < bin_num; i++)
		{
			for (int j = 0; j < bin_capacity; j++)
			{
				if (rand() % 100 < mutation_rate * 100)
				{
					if (bin[i][j] == 1)
					{
						bin[i][j] = 0;
					}
					else
					{
						bin[i][j] = 1;
					}
				}
			}
		}
	} 

public:
	void interation(int iter_num)
	{
		for (int i = 0; i < iter_num; i++)
		{
			selection();
			crossover();
			mutation();
			update_turntable();
		}
	}
private:
	int bin_capacity;//每箱容量,列
	int bin_num;//箱数,行
	int** bin;
	int* toTen;
	double* x;
	double* fitness;//适应度
	double* selected_rate;//被选择的概率
	double* turntable;
};