#include "machine.h"

Machine::Machine(string mn, int pr, set <string> s, set <char> a, vector <triple> dt, set <string> ins, set <string> outs)
{
	id = mn; //id
	priority = pr; //приоритет
	States = s; //количество состояний
	alphabeth = a; //алфавит
	delta = dt; //функции перехода
	S = ins; //начальные состояния
	F = outs; //заключительные состояния
	resm.first = false; //выход res
	resm.second = 0; //выход m
}

string Machine::getId() //геттер id
{
	return id;
}

int Machine::getPr() //геттер приоритета
{
	return priority;
}

pair <bool, int> Machine::maxString(string str, int k)
{
	resm.first = false;
	resm.second = 0;
	CurrentState = S;
	set <char>::iterator it;
	if (str.length() == 0 && finish(CurrentState)) //если стартовое состояние - заключительное
		resm.first = true;
	else {
		string buff = "";
		for (int i = k; i < str.length(); i++) //проход по строке
		{
			it = alphabeth.find(str[i]); //проверка совпадения текущего символа с алфавитом
			if (it == alphabeth.end())
				break;
			else
			{
				buff += str[i];
				CurrentState = transition(CurrentState, str[i]); //смена состояний
				if (finish(CurrentState)) //если среди текущих состояний есть заключительное
				{
					resm.first = true;
					resm.second = buff.length();
				}
			}
		}
	}
	return resm;
}

set <string> Machine::transition(set <string> state, char letter) //смена состояний
{
	set <string> buff;

	for (set <string>::iterator j = state.begin(); j != state.end(); j++)
		for (int i = 0; i < delta.size(); i++)
			if (delta[i].getIN() == *j && delta[i].getA() == letter)
				buff.insert(delta[i].getOUT());

	return buff;
}

bool Machine::finish(set <string> c) //проверка на заключительное состояние
{
	set <string>::iterator it;

	for (set <string>::iterator i = F.begin(); i != F.end(); i++)
		if (c.find(*i) != c.end())
			return true;

	return false;
}