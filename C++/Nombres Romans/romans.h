#pragma once

#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

static class Romans
{
public:
	Romans();
	~Romans();
	
	static int ROMaDEC(string a);
	static string DECaROM(int a);
private:
	static int getPosStr(string needle, char haystack);
	static string ch2str(char in);
};
string Romans::ch2str(char in) {
	stringstream ss;
	string t;
	ss << in;
	ss >> t;
	return t;
}
int Romans::getPosStr(string s, char c) {
	for (int i = 0; i < s.length(); i++)
		if (s.at(i) == c) return i;
	return -1;
}
int Romans::ROMaDEC(string r) {
	string nombres = "IVXLCDM";
	vector<int> valors = { 1,5,10,50,100,500,1000 };

	int res = 0;
	for (int i = r.length() - 1; i >= 0; i--) {
		res += valors.at(Romans::getPosStr(nombres, r.at(i)));
		for (int x = 0; x < Romans::getPosStr(nombres, r.at(i)); x++)
			valors.at(x) = -valors.at(x);
	}
	return res;
}
string Romans::DECaROM(int n) {
	if (n >= 4000 || n <= 0) return "Nombre massa gran (ha de ser menor a 4000)";
	
	string val = "IVXLCDM";
	string num = to_string(n);
	string res = "";
	int v = 0;
	for (int i = num.length() - 1; i >= 0; i--) {
		int x = num.at(i) - 48;
		if (x == 9) res = ch2str(val.at(2 * v)) + ch2str(val.at(2 * v + 2)) + res;
		if (x == 4) res = ch2str(val.at(2 * v)) + ch2str(val.at(2 * v + 1)) + res;
		if (x > 4 && x < 9) {
			for (int j = 0; j < x - 5; j++) res = ch2str(val.at(2 * v)) + res;
			res = ch2str(val.at(2 * v + 1)) + res;
		}
		if (x > 0 && x < 4)
			for (int j = 0; j < x; j++)
				res = ch2str(val.at(2 * v)) + res;
		v++;
	}
	return res;
}

Romans::Romans() {}

Romans::~Romans() {}