#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <string>
#include <array>
#include <Windows.h> // Al presionar ESC, se sortirà de l'execució del codi

// Se poden canviar aquestes variables
#define LIMIT 2000 // Limit de cel·les
#define LIMIT_BUCLE 10000 // Limit d'iteracions d'un bucle
#define ESTRICTE 1 // 0 per poder posar més d'1 byte a cada cel·le, 1 per impedir-ho

#define ESC 27 // aquesta no

using namespace std;

int ptr = 0;
array<int, LIMIT + 1> cells; // usarem arrays y no vectors, no farà falta afegir

typedef enum { PRINCIPAL, CELLS } RETURN; // Al ser una funció recursiva, necessitarem saber si l'execució és dintre un bucle o no

// Definicions de funcions
string simplificar(string c);
string error(string c);

void interpretar(string c, RETURN ret);

array<int, LIMIT + 1> interval(string c, array<int, LIMIT + 1> _int);

#pragma region Funcions de string (veure les funcions a PHP per a entendre el codi [mateix nom])
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

		int i = 1; // Per l'enumeració de línees
		while (a != "-exe" && i++) {
			codi += a;
			cout << i << ": ";
			getline(cin, a);
		}
		cout << "\n";
		codi = simplificar(codi); // Ignoram caràcters que no són "<>+-.,[]"
		
		cells.fill(0); // Plenam les cel·les amb zeros
		ptr = 0;

		try { // Si es genera un error, hem de sortir de tota la funció recursiva, per això, llançarem excepcions per aturar-les
			if ((e = error(codi)) != "ok") cout << e; // Massa tancaments o obriments de bucle
			else interpretar(codi, PRINCIPAL); // assenyalam que s'executi la funcio principal (per dir quan acaba l'execució)
		}
		catch (exception *e) { cout << "\n\n-------------------------------\nEl programa ha acabat: " << e->what(); } // En cas d'error
		
		cout << "\n\nDisposicio final de les 50 primeres cel.les:\n";
		
		for (int i = 0; i < 49; i++) cout << (int)cells.at(i) << "-";
		cout << (int)cells.at(50);
		
		_getch();
		system("cls");
	}
	return 0;
}

string out = ""; // 

void interpretar(string c, RETURN ret) {
	bool principal = ret == PRINCIPAL;
	if (principal) out = ""; // Evitar problemes si es processa més d'1 codi

	array<int, LIMIT + 1> _int;
	_int.fill(0);

	_int = interval(c, _int); // Tenim els intervals del bucles principals del codi, no els secundaris
	int inte = 0;

	for (int i = 0; i < c.length(); i++) {
		auto ch = c.at(i);
		if (GetAsyncKeyState(ESC) && ch != ',') throw new exception(); // Acabam execució si presionam ESC i no se mos demana un input

		if (ch == '>') ++ptr; // Increment del punter
		if (ch == '<') --ptr; // Decrement del punter
		if (ch == '+') { // Sumam 1 a la cel·la del punter, si tenim "#define ESTRICTE 1" i la cel·la sobrepassa 255, acabam l'execució
			++cells.at(ptr);
			if (ESTRICTE && cells.at(ptr) > 255) throw new exception(("\nError durant l'execucio: S'ha intentat asignar mes d'1 byte (255 en decimal) de memoria a la cel.la " + to_string(ptr + 1)).c_str());
		}
		if (ch == '-') { // Restam 1 a la cel·la actual
			--cells.at(ptr);
			if (ESTRICTE && cells.at(ptr) < 0) throw new exception(("\nError durant l'execucio: S'ha intentat asignar un valor negatiu per char [0,256) a la cel·la " + to_string(ptr + 1)).c_str());
		}
		if (ch == '.') { // Imprimim la cel·la actual com a char i no int
			out += (char)cells.at(ptr);
			cout << (char)cells.at(ptr);
		}
		if (ch == ',') { // Demanam un caràcter (per això, _getch() i no cin o getline())
			cout << "\nEsperant entrada de l'usuari: ";
			cells.at(ptr) = _getch();
			cout << "\n" << out;
		}			
		if (ch == '[') { // bucle
			i = _int.at(inte + 1); // obtenim quan es tanca
			string grup = substr(c, _int.at(inte) + 1, i - _int.at(inte) - 1); // ara grup serà el texte dintre el bucle

			int it = 0;
			while (cells.at(ptr) != 0) {
				it++;

				if (it > LIMIT_BUCLE) throw new exception("\nMassa iteracions d'un bucle."); // Evitar bucles infinits
				if (ptr < 0 || ptr >= LIMIT) throw new exception(("\nError durant l'execucio: Punter fora de l'interval. (" + to_string(ptr) + " no esta en l'interval [0, " + to_string(LIMIT - 1) + "])").c_str()); // El punter no pot sortir-se del nombre de cel·les (LIMIT)
				
				interpretar(grup, CELLS); // RECURSIÓ: interpretam el que hi ha dins el bucle, canviant el punter i la disposició de les cel·les (o feim per què pot haver-hi infinits bucles dins un (nested-loops), i per això usam funcions recursives
			}
			if (i >= c.length() - 1) break; // si se acaba el codi
			inte += 2 // Anirem al pròxim interval principal
		}
		if (ptr < 0 || ptr >= LIMIT) throw new exception(("\nError durant l'execucio: Punter fora de l'interval. (" + to_string(ptr) + " no esta en l'interval [0, " + to_string(LIMIT - 1) + "])").c_str());
	}
	if (principal) cout << "\n\n-------------------------------\nEl programa ha acabat satisfactoriament."; // Si és el principal, imprimirem que ha acabat bé, si no, s'ha llançat una excepció
}
array<int, LIMIT + 1> interval(string c, array<int, LIMIT + 1> _int) { // obtenim els intervals principals
	int pos = 0, count = 0;

	if (!strpos(c, '[')) return _int;
	int a0;
	int niv = 0; // Nivell de subordinació dels bucles

	for (int i = 0; i < c.length(); i++) {
		char a = c.at(i);
		if (a == '[') {
			if (niv == 0) a0 = i; // Si el nivell és 0 (no subordinat), obtenim l'inicial ('[')
			niv++;
		} if (a == ']') {
			niv--;
			if (niv == 0) { // Si el nivell és 0 (no subordinat), obtenim el final (']')
				_int.at(count) = a0;
				_int.at(count + 1) = i;
				count += 2; // Afegim [inicial, final], per això, afegim dos de cop i no un
			}
		}
	}
	return _int;
}
string simplificar(string c) { // Ignoram tots els caràcters que no pertanyin al codi BF
	string n;
	for (auto ch : c)
		if (ch == '>' || ch == '<' || ch == '+' || ch == '-' || ch == '.' || ch == ',' || ch == '[' || ch == ']') n += ch;
	return n;
}
string error(string c) { // Comprovam si hi ha els mateix nombre de començaments i final de bucle (si no, ni l'executarem, això és un poc de comprovar abans de executar, ho tenen tots els IDEs)
	int nivell = 0;
	for (auto ch : c) {
		if (ch == '[') nivell++;
		if (ch == ']') nivell--;

		if (nivell < 0) return "Vigila: massa tancaments de bucle";
	}
	if (nivell > 0) return "Vigila: bucle(s) sense tancar";
	return "ok";
}
