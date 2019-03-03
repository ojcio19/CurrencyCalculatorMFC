#include "stdafx.h"
#include "currency.h"
#include "helpFunction.h"

currency::currency(string a, string b, double c, double d) {
	code = a;
	name = b;
	buy = c;
	sell = d;
}

currency::~currency(){}
double exchange_values(string code, string code_2, double cash);
ostream& operator<< (ostream& out, currency& example);
istream& operator>> (istream& in, currency& example);



