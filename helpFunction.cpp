#include "stdafx.h"
#include <urlmon.h>
#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <fstream>

#include "helpFunction.h"

#pragma comment(lib,"urlmon.lib")


void download_current_state() {
	HRESULT nbp = URLDownloadToFile(NULL, L"https://www.nbp.pl/kursy/xml/lastc.xml", L"current_rates.xml", 0, NULL);
	if (nbp == S_OK) {}
	else if (nbp == E_OUTOFMEMORY) {
		cout << "Buffer length invalid, or insufficient memory\n";
	}
	else if (nbp == INET_E_DOWNLOAD_FAILURE) {
		cout << "URL is invalid\n";
	}
	else {
		cout << "Other error: %d\n" << nbp;
	}
}

double comma_to_dot(string com) {
	for (int i = 0; i < com.length(); i++) {
		if (com[i] == ',')	com[i] = '.';
	}
	return stod(com);
}

vector<currency> load_data(vector<string> *s) {
	download_current_state();
	fstream file;
	file.open("current_rates.xml", ios::in);
	if (file.good() == false)
	{
		cout << "There is no file to open" << endl;
	}

	vector<currency> example;
	vector<string> nazwa, kod;
	vector<double> buy, sell;
	vector<int> decurion;			//przelicznik
	string line;
	/*dodanie zlotowek*/
	nazwa.push_back("zloty");
	decurion.push_back(1);
	kod.push_back("PLN");
	buy.push_back(1);
	sell.push_back(1);

	while (getline(file, line)) {
		regex pattern("<nazwa_waluty>(.*)</nazwa_waluty>");
		smatch score;
		if (regex_search(line, score, pattern))
		{
			nazwa.push_back(score[1]);
		}
	pattern = "<przelicznik>(.*)</przelicznik>";
		if (regex_search(line, score, pattern))
		{
			decurion.push_back(stoi(score[1]));
		}
	pattern = "<kod_waluty>(.*)</kod_waluty>";
		if (regex_search(line, score, pattern))
		{
			kod.push_back(score[1]);
		}
	pattern = "<kurs_kupna>(.*)</kurs_kupna>";
		if (regex_search(line, score, pattern))
		{
			buy.push_back(comma_to_dot(score[1]));
		}
	pattern = "<kurs_sprzedazy>(.*)</kurs_sprzedazy>";
		if (regex_search(line, score, pattern))
		{
			sell.push_back(comma_to_dot(score[1]));
		}
	}

	vector<string > to_return;
	for (int i = 0; i < nazwa.size(); i++) {
		currency make_new(kod[i], nazwa[i], buy[i]/decurion[i], sell[i]/decurion[i]);
		example.push_back(make_new);
		to_return.push_back(kod[i]);
	}
	*s = to_return;
	file.close();
	return example;
}

double exchange_values(string code, string code_2, double cash)
{
	vector<string> xd;
	vector<currency> table = load_data(&xd);
	/*zainicjowanie zmiennych*/
	double exchange_buy = 1;
	double exchange_sell = 1;
	double result = 0.0;
	
	for (int i = 0; i < table.size(); i++){
		if (table[i].code == code){
			exchange_buy = table[i].buy;
		}
		if (table[i].code == code_2){
			exchange_sell = table[i].sell;
		}
	}
	
	if (exchange_sell != 0){
		result = (exchange_buy / exchange_sell)*cash;
	}
	else
		cout << "Fatal error" << endl;
	return result;
}

vector<string> giveCodes()
{
	vector<string> code_tab;
	vector<currency> xd =  load_data(&code_tab);  
	return code_tab;
}