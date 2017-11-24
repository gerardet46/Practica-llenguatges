#include <stdio.h>
#include <math.h>

int min(int a, int b) {return a <= b ? a : b;}
int max(int a, int b) {return a >= b ? a : b;}
int mincd(int a, int b) {
	if (a < 2 || b < 2) return 0;
	int i, c = min(a,b);

	for (i = 2; i <= c; i++)
		if (a % i == 0 && b % i == 0) return i;
	return 1;
}
int mcd(int a, int b) {
	if (a == b) return a;

	int i, c = min(a,b);
	for (i = c; i > 1; i--)
		if (a % i == 0 && b % i == 0) return i;
	return 1;
}
int mcm(int a, int b) {
	if (a == b) return a;
	int i, c = max(a,b), d = min(a,b);

	for (i = c; i < a * b; i += c)
		if (i % d == 0) return i;
	return a * b;
}
int primo(int a) { // si retorna > 0 -> no es cosi, si no ho es
	if (a < 2) return 1;
	if (a % 2 == 0) return 2;

	for (int i = 3; i <= (int)sqrt(a); i += 2)
		if (a % i == 0) return i;
	return 0;
}

int main()
{
	int sortir = 1;
	while (sortir) {
		system("cls");

		printf("Escriu mode:\n1 => MinCD\n2 => MCM\n3 => MCD\n4 => si x es cosi\n5 => Sortir\n");
		char a = getch();
		system("cls");
		switch (a) {
			case '1': {
				int a, b;
				printf("Escriu el primer numero (> 2): ");
				scanf("%d", &a);
				printf("Escriu el segon numero (> 2): ");
				scanf("%d", &b);
				printf("-----------------------------\nEl MinCD de %d i %d es %d", a, b, mincd(a,b));
				getch();
				break;
			}
			case '2': {
				int a, b;
				printf("Escriu el primer numero (> 2): ");
				scanf("%d", &a);
				printf("Escriu el segon numero (> 2): ");
				scanf("%d", &b);
				printf("-----------------------------\nEl MCM de %d i %d es %d", a, b, mcm(a,b));
				getch();
				break;
			}
			case '3': {
				int a, b;
				printf("Escriu el primer numero (> 2): ");
				scanf("%d", &a);
				printf("Escriu el segon numero (> 2): ");
				scanf("%d", &b);
				printf("-----------------------------\nEl MCD de %d i %d es %d", a, b, mcd(a,b));
				getch();
				break;
			}
			case '4': {
				int a;
				printf("Escriu el numero: ");
				scanf("%d", &a);
				printf("-----------------------------\n%d%s es cosi", a, primo(a) ? "NO");
				getch();
				break;
			}
			case '5': {
				sortir = 0;
				break;
			}
		}
	}
	return 0;
}
