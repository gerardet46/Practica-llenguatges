#include <iostream>
#include <string>
#include <stdlib.h>
#include <conio.h>
#include <thread>
#include <chrono>

#define SPACE 32

using namespace std;

int vides = 0;
string errors = "";
string toup(string inp) {
	string r = "";
	for (int i = 0; i < inp.length(); i++) {
		if (inp.at(i) < 97) r += inp.at(i);
		else r += (inp.at(i) - 32);
	}
	return r;
}
string plenar(string input, string dashed, char pl) {
	if (pl > 92) pl -= 32;
	bool hiha = false;
	for (int i = 0; i < input.length(); i++)
		if (input.at(i) == pl) {
			dashed.at(i) = pl;
			hiha = true;
		}
	system("cls");
	if (!hiha) {
		vides--;

		if (errors == "") errors = "Errades => ";
		else errors += ", ";
		errors += pl; 
		
		cout << "Has fallat!!!";
	} else cout << "Molt be!!!";
	return dashed;
}
bool str_include(string input, char c) {
	for (int i = 0; i < input.length(); i++)
		if (input.at(i) == c) return true;
	return false;
}
int main() {
	while (true) {
		system("cls");

		errors = "";
		string p = "", g = "", vid = "";

		cout << "Introdueix paraula/frase, J1: ";
		getline(cin, p);
		p = toup(p);

		system("cls");

		cout << "Introdueix nombre de vides: ";
		cin >> vid;
		vides = stoi(vid);

		for (int i = 0; i < p.length(); i++) {
			if (p.at(i) == SPACE) g += SPACE;
			else g += '-';
		}
		g = plenar(p, g, p.at(0));

		bool perdut = false;
		while (str_include(g, '-')) {
			if (vides == 0) {
				perdut = true;
				break;
			}
			system("cls");
			cout << g << "\n\nVides => " << vides << "\n" << errors << "\n\n1 => Escriure caracter\n2 => Escriure paraula/frase";
			char mode = _getch();

			system("cls");
			if (mode == '1') {
				cout << g << "\n\nEsriu el caracter: ";
				char c = _getch();
				g = plenar(p, g, c);
				this_thread::sleep_for(chrono::milliseconds(1500));
			} else if (mode == '2') {
				cout << g << "\n\nEscriu la paraula/frase: ";
				string ne = "";
				getline(cin, ne);
				ne = toup(ne);
				if (ne == p) g = p; // completat
				else vides--;
			}
		}
		system("cls");

		if (perdut) cout << "T'has quedat sense vides!!!!!\n";
		else cout << "Enhorabona!!!!!";

		cout << "\nLa paraula/frase era " << p << "\n\n1 => Sortir\nQualsevol altre caracter => Fer-ne una altra";
		char mod = _getch();
		if (mod == '1') break;
	}
	return 0;
}
