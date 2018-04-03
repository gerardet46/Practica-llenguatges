#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <string>
#include <array>
#include <Windows.h>

// Se poden canviar aquestes variables
#define LIMIT 2000
#define LIMIT_BUCLE 10000
#define ESTRICTE 0

#define ESC 27 // aquesta no

using namespace std;

int ptr = 0;
array<int, LIMIT + 1> cells;

typedef enum { PRINCIPAL, CELLS } RETURN;

string simplificar(string c);
string error(string c);

void interpretar(string c, RETURN ret);

array<int, LIMIT + 1> interval(string c, array<int, LIMIT + 1> _int);

#pragma region Funcions de string
bool strpos(string a, char c) {
	for (auto ch : a)
		if (ch == c) return true;
	return false;
}
string substr(string s, int start, int len) {
	string n = "";
	for (int i = 0; i < len; i++)
		n += s.at(start + i);
	return n;
}
#pragma endregion

int main() {
	while (true) {
		cout << "Introduiex linees de codi BF (per executar, escriu a una nova linea \"-exe\", per aturar execucio, presionar ESC):\n1: ";
		string a, codi, e;
		getline(cin, a);

		int i = 1;
		while (a != "-exe" && i++) {
			codi += a;
			cout << i << ": ";
			getline(cin, a);
		}
		cout << "\n";
		codi = simplificar(codi);
		
		cells.fill(0);

		int ptr = 0;

		try {
			if ((e = error(codi)) != "ok") cout << e;
			else interpretar(codi, PRINCIPAL);
		}
		catch (exception *e) { cout << "\n\n-------------------------------\nEl programa ha acabat: " << e->what(); }
		
		cout << "\n\nDisposicio final de les 50 primeres cel.les:\n";
		
		for (int i = 0; i < 49; i++) cout << (int)cells.at(i) << "-";
		cout << (int)cells.at(50);
		
		_getch();
		system("cls");
	}
	return 0;
}

string out = "";

void interpretar(string c, RETURN ret) {
	bool principal = ret == PRINCIPAL;

	array<int, LIMIT + 1> _int;
	_int.fill(0);

	_int = interval(c, _int);
	int inte = 0;

	for (int i = 0; i < c.length(); i++) {
		auto ch = c.at(i);
		if (GetAsyncKeyState(ESC) && ch != ',') throw new exception();

		if (ch == '>') ++ptr;
		if (ch == '<') --ptr;
		if (ch == '+') {
			++cells.at(ptr);
			if (ESTRICTE && cells.at(ptr) > 255) throw new exception(("\nError durant l'execucio: S'ha intentat asignar mes d'1 byte (255 en decimal) de memoria a la cel.la " + to_string(ptr + 1)).c_str());
		}
		if (ch == '-') --cells.at(ptr);
		if (ch == '.') {
			out += (char)cells.at(ptr);
			cout << (char)cells.at(ptr);
		}
		if (ch == ',') {
			cout << "\nEsperant entrada de l'usuari: ";
			cells.at(ptr) = _getch();
			cout << "\n" << out;
		}			
		if (ch == '[') {
			i = _int.at(inte + 1);
			string grup = substr(c, _int.at(inte) + 1, i - _int.at(inte) - 1);

			int it = 0;
			while (cells.at(ptr) != 0) {
				it++;

				if (it > LIMIT_BUCLE) throw new exception("\nMassa iteracions d'un bucle.");
				if (ptr < 0 || ptr >= LIMIT) throw new exception(("\nError durant l'execucio: Punter fora de l'interval. (" + to_string(ptr) + " no esta en l'interval [0, " + to_string(LIMIT - 1) + "])").c_str());
				
				interpretar(grup, CELLS);			
			}
			if (i >= c.length() - 1) break;
			while (_int.at(inte += 2) < i && inte < LIMIT);
		}
		if (ptr < 0 || ptr >= LIMIT) throw new exception(("\nError durant l'execucio: Punter fora de l'interval. (" + to_string(ptr) + " no esta en l'interval [0, " + to_string(LIMIT - 1) + "])").c_str());
	}
	if (principal) cout << "\n\n-------------------------------\nEl programa ha acabat satisfactoriament.";
}
array<int, LIMIT + 1> interval(string c, array<int, LIMIT + 1> _int) {
	int pos = 0, count = 0;

	if (!strpos(c, '[')) return _int;
	int a0;
	int niv = 0;

	for (int i = 0; i < c.length(); i++) {
		char a = c.at(i);
		if (a == '[') {
			if (niv == 0) a0 = i;
			niv++;
		} if (a == ']') {
			niv--;
			if (niv == 0) {
				_int.at(count) = a0;
				_int.at(count + 1) = i;
				count += 2;
			}
		}
	}
	return _int;
}
string simplificar(string c) {
	string n;
	for (auto ch : c)
		if (ch == '>' || ch == '<' || ch == '+' || ch == '-' || ch == '.' || ch == ',' || ch == '[' || ch == ']') n += ch;
	return n;
}
string error(string c) {
	int nivell = 0;
	for (auto ch : c) {
		if (ch == '[') nivell++;
		if (ch == ']') nivell--;

		if (nivell < 0) return "Vigila: massa tancaments de bucle";
	}
	if (nivell > 0) return "Vigila: bucle(s) sense tancar";
	return "ok";
}