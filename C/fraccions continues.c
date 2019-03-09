// Info sobre fraccions contínues: https://en.wikipedia.org/wiki/Continued_fraction
// Farem servir la notació compactada [a0; a1, a2, ..., an] per no haver d'escriure les fraccions com a tal

#pragma warning (disable : 4996)

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>

int pow(int a, int b) {
	int r = 1;
	for (int i = 0; i < b; i++) r *= a;
	return r;
}
// Comprovar si l'string té el format correcte
int es_contfrac(char* c) {
	int obertura = 0, tancat = 0, primer = 0;
	for (int i = 0; i < strlen(c); i++) {
		if (c[i] != ' ') {
			if (tancat) return 0;

			if (c[i] == '[') {
				if (obertura) return 0;
				else obertura = 1;
			}
			else if (c[i] == ']') tancat == 1;
			else if (c[i] == ';') {
				if (primer) return 0;
				else primer = 1;
			}
			else if (c[i] == ',' && !primer) return 0;
			else if (c[i] < '0' || c[i] > '9') return 0;
		}
	}
	return 1;
}
int main() {
	while (1) {
		// Menú principal
		int mode = 0;
		printf("1 => p/q -> fraccio continua\n2 => fraccio continua -> p/q\nAltre => esborrar");
		mode = getch();

		if (mode == '1') {
			int p, q;
			int primer = 1;

			// Demanam p i q
			printf("\n----------------------------\n1 numero: ");
			scanf("%i", &p);
			printf("2 numero: ");
			scanf("%i", &q);
			/*
			Sabem que el primer coeficient és floor(p/q), atès que 1/x < 0, x > 1. Per tant, tenim
			p/q = floor(p/q) + 1/x => x = q/(p - q * floor(p/q))
			I podem repetir el procés cíclicament per c fins que sigui un enter.

			* Recordam que si la fracció contínua és finita, aleshores és racional; sinó és irracional.
			Com demanam p/q, sempre tornarem una fracció contínua finita
			*/
      if (q == 0) {
				printf("Divisio per 0\n\n", p / q);
				continue;
			}
      
			double div = (double)p / q;
			if (p % q == 0) {
				printf("%i\n\n", p / q);
				continue;
			}
			printf("\n[%i; ", (int)div);

			while (p % q) {
				int np = q;
				int nq = p - q * (int)div;

				q = nq;
				p = np;
				div = (double)p / q;

				if (primer) primer = 0;
				else printf(", ");

				// Imprimim el nou coeficient
				printf("%i", (int)div);
			}
			printf("]");
			printf("\n---------------------------\n");
		}
		else if (mode == '2') {
			char frac[256];
			int data[100];

			printf("\n-----------------------------\nfraccio continua: ");
			scanf("%[^\n]s", frac);

			// Comprovam si l'input té el format correcte ("[a0; a1, a2, a3, ..., an]")
			if (!es_contfrac(frac)) {
				printf("\nFormat no valid");
				printf("\n---------------------------\n");
				int x;
				while ((x = getchar()) != '\n' && x != EOF);
				continue;
			}

			// Col·locam tots els coeficients en char* en l'array data, que serà més fàcil calcular
			int index = -1, num = -1, potencia = 0;
			for (int i = strlen(frac) - 2; i >= 0; i--) {
				if (frac[i] == ' ') continue;
				if (frac[i] <= '9' && frac[i] >= '0') {
					if (num == -1) num = frac[i] - '0';
					else num += (frac[i] - '0')*pow(10, ++potencia);
				}
				else if (num >= 0) {
					data[++index] = num;
					num = -1;
					potencia = 0;
				}
			}
			// "data" té els index a l'inrevés

			/*
			Sigui "a" el darrer coeficient.
			Sigui "b" el avantdarrer coeficient.
			Sigui "c" el nombre que correspon a (b + c/a), que inicialment sempre serà 1.

			Aleshores,
			1/(b + c/a) = 1/((b * a + c) / a) = a / (b * a + c)
			Per tant:
			a' = b * a + c, (darrer coeficient)
			c' = a (el nombre del numerador)
			b' = coeficient de l'array següent
			*/
			int a = data[0], b = data[1], c = 1;
			for (int i = 2; i <= index; i++) {
				int nc = a;
				int na = a * b + c;

				a = na;
				b = data[i];
				c = nc;
			}
			int na = a;
			int nc = a * b + c;
			c = nc;
			a = na;

			printf("\n%i/%i = %f", c, a, (double)c / a);
			printf("\n---------------------------\n");
		}
		else system("cls");

		if (mode == '1' || mode == '2') {
			int x;
			while ((x = getchar()) != '\n' && x != EOF);
		}
	}
	return 0;
}
