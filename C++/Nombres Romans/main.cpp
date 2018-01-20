#include <regex>
#include "romans.h"

int main() {
	while (true) {
		cout << "Escriu un nombre roma o algebraic (p => veure tots, q => sortir):\n";
		char cmd = _getch();
		if (cmd == 'p' || cmd == 'P') {
			for (int i = 1; i < 4000; i++) cout << i << " => " << Romans::DECaROM(i) << "\n";
			cout << "----------------------\nPresiona tecla per continuar";
			_getch();
		}

		else if (cmd == 'q' || cmd == 'Q')break;
		else {
			string r = "";
			cin >> r;

			regex nombre("^\\+?[[:digit:]]+$"), roma("^M{0,3}(D|CM|CD|D?C{1,3})?(L|XC|XL|L?X{1,3})?(V|IX|IV|V?I{1,3})?$");
			if (r.length() > 0) {
				if (regex_match(r, nombre)) {
					if (stoi(r) > 4000 || stoi(r) < 0) cout << "Nombre fora d'interval";
					else cout << "----------------------\nEl nombre en roma es " << Romans::DECaROM(stoi(r));
				}
				else if (regex_match(r, roma)) {
					cout << "----------------------\nEl nombre en algebraic es " << Romans::ROMaDEC(r);
				}
				else cout << "Entrada no valida";
			}
			_getch();		
		}
		system("cls");
	}
	return 0;
}