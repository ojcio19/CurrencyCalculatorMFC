#pragma once
#include <iostream>

using namespace std;

class currency{
	string code;
	string name;
	double buy;
	double sell;
public:
	currency(string = "", string = "", double = 0, double = 0); //constructor
	~currency();
	friend double exchange_values(string code, string code_2, double cash);
	friend ostream& operator<< (ostream& out, currency& example);
	friend istream& operator>> (istream& in, currency& example);
};

