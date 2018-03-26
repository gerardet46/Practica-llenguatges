#include <iostream>
#include <string>
#include <conio.h>
#include <time.h>
#include <stdlib.h>

using namespace std;

int main(int argc, char const *argv[])
{
	srand(time(NULL));
	while (true) {
		system("cls");
		cout << "1 => Generar numero aleatori de x xifres\n2 => Sortir";
		char r = getch();

		system("cls");
		if (r == '1') {
			int num;
			cout << "Entra el numero de xifres: ";
			cin >> num;
			cout << (1 + rand() % 9);

			string r = "";
			for (int i = 1; i < num; i++) {
				int n = rand() % 10;
				cout << n;
				r += n;
			}
			cout << "\nNombre copiat";
			getch();
		} else if (r == '2') break;
	}
	return 0;
}
