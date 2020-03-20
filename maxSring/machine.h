#pragma once
#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <string>

using namespace std;

class triple //класс тройки
{
public:
	triple(string in, char a, string out);
	triple();
	string getIN();
	string getOUT();
	char getA();;
	void setIN(string in);
	void setA(char a);
	void setOUT(string out);
private:
	string input;
	char letter;
	string output;
};

class Machine
{
public:
	Machine(string mn, int pr, set <string> s, set <char> a, vector <triple> dt, set <string> ins, set <string> outs); //конструктор автомата
	pair <bool, int> maxString(string str, int k); //maxString
	string getId(); //возврат id
	int getPr(); //возврат приоритета
	set <string> transition(set <string> state, char letter); //смена состояний
	bool finish(set <string> c); //проверка на заключительное состояние

private:
	int priority;
	string id;
	set <char> alphabeth;
	pair <bool, int> resm;
	set <string> States;
	set <string> CurrentState, S, F;
	vector <triple> delta;
};