#include <iostream>
#include <string>
#include <stdio.h>
#include <chrono>
#include <thread>
#include <regex>
#include <conio.h>
#include <sstream>

using namespace std;

int max(int a, int b) { return a >= b ? a : b; }
int min(int a, int b) { return a <= b ? a : b; }

string sumar(string a, string b) {
	int l1 = max(a.length(), b.length()), l2 = min(a.length(), b.length());
	string c = a.length() == l1 ? a : b; // string amb mes tamany
	string d = c == a ? b : a; // string amb menys tamany
	while (d.length() < c.length()) d = "0" + d;

	string resultat;
	int x, y = 0;
	for (int i = c.length() - 1; i >= 0; i--) {
		string s1, s2;
		stringstream ss1, ss2;
		ss1 << c[i]; ss1 >> s1;
		ss2 << d[i]; ss2 >> s2;

		x = stoi(s1) + stoi(s2) + y;
		if (x > 9) {
			x -= 10;
			y = 1;
		}
		else y = 0;
		resultat = to_string(x) + resultat;
	}
	return y == 1 ? to_string(y) + resultat : resultat;
}

int main() {
	bool sortir = true;
	while (sortir) {
		system("cls");

		cout << "Presiona Mode\n1 => Sumar numeros grans\n2 => Sortir\n";
		char r = _getch();
		system("cls");

		string a = "", b = "";
		regex rx("\\+?[[:digit:]]+");
		switch (r)
		{
		case '1':
			do {
				cout << "Indrodueix el primer numero: ";
				cin >> a;
				cout << "Indrodueix el segon numero: ";
				cin >> b;
				if (!regex_match(a, rx) || !regex_match(b, rx)) {
					cout << "Entrada no valida.";
					this_thread::sleep_for(chrono::milliseconds(1500));
					system("cls");
				}
			} while (!regex_match(a, rx) || !regex_match(b, rx));
			cout << "Es resultat de sa suma es:\n" << sumar(a, b);
			_getch();
			break;

		case '2':
			sortir = false;
			break;

		default:
			cout << "Entrada incorrecta";
			this_thread::sleep_for(chrono::milliseconds(1500)); // 1'5s
			break;
		}
	}
	return 0;
}
