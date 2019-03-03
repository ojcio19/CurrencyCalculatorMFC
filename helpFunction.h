#pragma once
#include <iostream>
#include <vector>

#include "currency.h"

using namespace std;


void download_current_state();

double comma_to_dot(string com);

vector<currency> load_data(vector<string> *s);

double exchange_values(string code, string code_2, double cash);

vector<string> giveCodes();