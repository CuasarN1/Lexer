#include <iostream>
#include <fstream>
#include "machine.h"

int main()
{
	string path = "automato", menu = "";
	int depth, num = 1;

	cout << "-------------------------------------" << endl;
	cout << "| root/"<<path<<num<<".txt                |" << endl;
	cout << "| Текущий адрес автомата. Изменить? |" << endl;
	cout << "| 1 - Да                            |" << endl;
	cout << "| 2 - Нет                           |" << endl;
	cout << "-------------------------------------" << endl;
	cin >> menu;
	if (menu == "1")
	{
		cout << "Введите новый адрес файла" << endl;
		cin >> path;
	}

	char letter;
	set <char> a;
	set <string> s, ins, outs;
	vector <triple> dt;

	string state, id, str, str2, str3;
	vector <Machine> machines;
	bool stop = false;
	int priority;

	while (!stop)
	{
		state = to_string(num);
		ifstream in;
		in.open(path + state + ".txt");
		if (in.is_open()) //файл успешно открыт
		{
			getline(in, id); //id

			in >> priority; //приоритет
			getline(in, state);

			in >> depth;
			getline(in, state);
			for (int i = 1; i <= depth; i++) //все состояния
			{
				getline(in, state);
				s.insert(state);
			}

			in >> depth;
			for (int i = 0; i < depth; i++) //алфавит
			{
				in >> letter;
				a.insert(letter);
			}

			in >> depth;
			getline(in, str);
			for (int i = 0; i < depth; i++) //функции переходов
			{
				str = str2 = str3 = "";
				int j = 0;
				getline(in, str);
				while (isalpha(str[j]) != 0)
				{
					str2 += str[j];
					j++;
				}

				letter = str[j + 1];

				for (int l = j + 3; l < str.length(); l++)
					str3 += str[l];

				triple delta(str2, letter, str3);
				dt.push_back(delta);

			}

			in >> depth;
			getline(in, state);
			for (int i = 0; i < depth; i++) //начальные состояния
			{
				getline(in, state);
				ins.insert(state);
			}

			in >> depth;
			getline(in, state);
			for (int i = 0; i < depth; i++) //заключительные состояния
			{
				getline(in, state);
				outs.insert(state);
			}
			Machine automato(id, priority, s, a, dt, ins, outs);
			machines.push_back(automato); //вектор автоматов
		}
		else
			stop = true;

		in.close();
		num++; //счетчик автоматов
		a.clear();
		s.clear();
		ins.clear();
		outs.clear();
		dt.clear();
	}

	int k, m;

	cout << "Введите слово и k-ую позицию" << endl;
	cin >> str >> k;

	int length = str.length();
	bool inc, flag = false;
	pair <bool, int> result;
	path = "output.txt";
	ofstream out;
	out.open(path);
	if (out.is_open()) //файл успешно открыт
	{
		while (k < length) //проход по строке
		{
			priority = -1;
			m = 0;
			inc = true;
			result.first = false;
			result.second = 0;
			for (int j = 0; j < num - 2; j++) //проход по автоматам
			{
				result = machines[j].maxString(str, k);
				if (result.first) // если maxString нашел подходящую подстроку
				{
					if (result.second > m) //если подстрока длиннее остальных
					{
						m = result.second;
						priority = machines[j].getPr();
						id = machines[j].getId();
					}
					else if (m == result.second && priority < machines[j].getPr()) //если подстрока такой же длинны, но приоритет этого автомата выше
					{
						m = result.second;
						priority = machines[j].getPr();
						id = machines[j].getId();
					}

					inc = false;
					flag = true;
				}
			}
			if (inc) //если ни один автомат не нашел подходящей подстроки
				k++;
			else
			{
				k += m;
				out << id << ' ' << k - m << ' ' << k - 1 << ' ';
				for (int i = k - m; i < k; i++)
					out << str[i];
				out << endl;
			}
		}
		if (!flag) //строка не удовлетворяет ни одному автомату
			out << "false 0" << endl;
	}
	else
		cout << "Файла для записи не существует!";

	return 0; 
}