#include "machine.h"

triple::triple(string in, char a, string out) //конструктор тройки
{
	input = in;
	letter = a;
	output = out;
}

triple::triple()
{

}

string triple::getIN()
{
	return input;
}

string triple::getOUT()
{
	return output;
}

char triple::getA()
{
	return letter;
}

void triple::setIN(string in)
{
	input = in;
}

void triple::setA(char a)
{
	letter = a;
}

void triple::setOUT(string out)
{
	output = out;
}