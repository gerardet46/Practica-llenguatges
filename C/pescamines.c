#pragma warning (disable : 4996)

/*Cal recordar que el mètode scanf atura quan es troba amb '\s' o EOF ('\n'). Per tant, el programa es basa en agafar arguments separats
per espais (x y z), és a dir, diversos scanf. Per això, haurem d'esborrar l'entrada de l'usuari si introduix més dades de les necessàries
*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>

// Definim els colors de sortida de la consola
#define COL_RED     "\x1b[31m"
#define COL_GREEN   "\x1b[32m"
#define COL_YELLOW  "\x1b[33m"
#define COL_BLUE    "\x1b[34m"
#define COL_MAGENTA "\x1b[35m"
#define COL_CYAN    "\x1b[36m"
#define COL_RESET   "\x1b[0m"

// Esborrar el stdin (entrada de l'usuari) per a evitar problemes amb scanf (ja que escaneja per espais)
#define ESBORRAR while (getchar() != '\n');
// Caràcter a emprar quan la cel·la no se mostri
#define BLANC '.'

// Per a acursar (usarem molt aquestes expressions)
#define VEI camp[camp[i].veins[j]]
#define EXISTEIX_VEI camp[i].veins[j] != -1
#define BUCLE_VEI for (int j = 0; j < 8; j++)

typedef enum ESTATS {MENU, JUGANT, GUANYAT, PERDUT} estat;

// Definirem un camp ple de cel·les (aquesta estructura)
struct cell {
	int bandera, bombes_devora, veins[8], bomba;
	char toString;
};

char opt; // Per desar la variable del menú principal
int cols = 9, files = 9, sz = 81, mines = 10, banderes, primer_torn = 1, segons, minuts;
estat partida = MENU;
struct cell camp[3600]; // El tamany màxim del camp és 60x60 (normalment no els usam tots)

int pt;
void biuni(int _x, int _y) {pt = _y * cols + _x;} // IMPORTANT! Desam el resultat en la variable "pt"

// Mètode per mostrar una cel·la (nombre de bombes devora, si és una bomba o està en blanc)
void mostrar_cella(int index) {
	if (camp[index].bomba) camp[index].toString = 'x';
	else if (!camp[index].bombes_devora) camp[index].toString = ' ';
	else camp[index].toString = camp[index].bombes_devora + '0';
}
// Mètode per reiniciar el camp
void reiniciar_cells() {
	int x_inc = 0;
	for (int i = 0; i < sz; i++) {
		camp[i].bandera = camp[i].bombes_devora = camp[i].bomba = 0;
		camp[i].toString = BLANC;
		BUCLE_VEI camp[i].veins[j] = -1; // Esborram tots els veïns

		if (++x_inc > cols) x_inc = 1;

		// calcular veïns (en total 8)
		if (i - cols >= 0) camp[i].veins[0] = i - cols; // N
		if (x_inc < cols) camp[i].veins[1] = i + 1; // E
		if (i + cols < sz) camp[i].veins[2] = i + cols; // S
		if (x_inc > 1) camp[i].veins[3] = i - 1; // O

		if (x_inc < cols && i - cols >= -1) camp[i].veins[4] = i - cols + 1; // NE
		if (x_inc < cols && i + cols + 1 < sz) camp[i].veins[5] = i + cols + 1; // SE
		if (x_inc > 1 && i + cols - 1 < sz) camp[i].veins[6] = i + cols - 1; // SO
		if (x_inc > 1 && i - cols > 0) camp[i].veins[7] = i - cols - 1; // NO
	}
	// Col·locar mines (aleatori)
	int _mines = 0;
	while (_mines < mines) {
		int casella = rand() % sz;
		if (!camp[casella].bomba && ++_mines) camp[casella].bomba = 1; // Només col·locar una mina si en la casella actual no n'hi ha cap
	}

	// Contar nombre de mines devora cada casella (Per mostrar a l'usuari i per destapar bé les caselles
	for (int i = 0; i < sz; i++) {
		int conta = 0;
		BUCLE_VEI if (EXISTEIX_VEI && VEI.bomba) conta++;
		camp[i].bombes_devora = conta;
	}
}
// Mètodes recursius per desvetllar les caselles de devora
void destapar_veins(int i);
void destapar(int i) {
	BUCLE_VEI
		if (EXISTEIX_VEI && !VEI.bomba)
			destapar_veins(camp[i].veins[j]);
}
void destapar_veins(int i) {
	mostrar_cella(i);
	BUCLE_VEI{
		if (EXISTEIX_VEI && !VEI.bomba && !VEI.bombes_devora && (VEI.toString == BLANC || VEI.toString == 'f')) {
      // Si la casella no té mines devora, imprimirem més veïns
			VEI.toString = ' ';
			destapar(camp[i].veins[j]);
		}
	}
}
// Mètode per imprimir el taulell
void render() {
	printf("'-1' i intro per sortir del joc.\n\nMines\: %d\nTemps\: %02d\:%02d\n\n", mines - banderes, minuts, segons);

	for (int i = 0; i < files; i++) {
		if (!i) {
			// Dibuixam índex de files
			printf("  |");
			for (int j = 0; j < cols; j++) printf(" %02d", j + 1);
			printf(" |\n");
			for (int i = 0; i <= cols; i++) printf("---");
			printf("----\n");
		}
		for (int j = 0; j < cols; j++) {		
			if (!j) printf("%02d|", i + 1); // Dibuixam índex de columnes
			biuni(j, i);
			if (camp[pt].toString == BLANC) printf(COL_CYAN "  %c" COL_RESET, BLANC);
			else if (camp[pt].toString == 'f') printf(COL_YELLOW "  f" COL_RESET);
			else if (camp[pt].bomba) printf(COL_RED "  x" COL_RESET);
			else printf(COL_GREEN "  %c" COL_RESET, camp[pt].toString);
		}
		printf(" | %02d\n", i + 1);
	}
	for (int i = 0; i <= cols; i++) printf("---");
	printf("----\n  |");
	for (int i = 0; i < cols; i++) printf(" %02d", i + 1);
	printf(" |");
	if (partida == JUGANT) printf("\n\nIntrodueix les coordenades (['0' si vols posar/llevar marca]) [columna] [fila]:\n");
}

// Punt d'entrada
int main() {
	srand(time(NULL)); // Fer que la distribució del taulell sigui diferent cada pic que entram

	while (1) {
		system("cls");
		system("title Pescamines");
		segons = minuts = banderes = 0;
		
		// Pantalla principal (menú)
		printf("Selecciona mode:\n1 => Principiant (9x9, 10 mines)\n2 => Intermedi (16x16, 40 mines)\n3 => Expert (30x16, 99 mines)\n4 => Personalitzat");
		do opt = _getch(); while (opt < '1' || opt > '4');

		system("cls");

		switch (opt) {
		case '1':
			cols = files = 9;
			mines = 10;
			system("title Pescamines (Mode Principiant)");
			break;
		case '2':
			cols = files = 16;
			mines = 40;
			system("title Pescamines (Mode intermedi)");
			break;
		case '3':
			cols = 30;
			files = 16;
			mines = 99;
			system("title Pescamines (Mode Expert)");
			break;
		case '4': // En cas de triar distribució personalitzada
			printf("Escriu les configuracions en el format seguent: [cols] [files] [bombes] (nomes numeros separats per espais o intros):\n");

		personalitzat:
			system("title Pescamines (Mode Personalitzat)");
			scanf("%d", &cols); // Escanejam les columnes, les files i el nombre de mines
			scanf("%d", &files);
			scanf("%d", &mines);

			if (cols < 5 || cols > 60) { // Comprovar si el nombre de columnes és incorrecte
				printf("\nRecorda: 5 <= cols <= 60\n");
				ESBORRAR
				goto personalitzat;
			}
			if (files < 5 || files > 60) { // Comprovar si el nombre de files és incorrecte
				printf("\nRecorda: 5 <= files <= 60\n");
				ESBORRAR
				goto personalitzat;
			}
			sz = cols * files;
			float freq = mines / (float)sz;
			if (freq < 0.05 || freq > 0.5) { // Comprovar si n'hi ha el nombre de bombes adequat (calculant la probabilitat de trobar-se'n una)
				printf("\nLa probabilitat de trobar una mina ha de ser: 0.05 <= P() <= 0.5");

				int _min = ceil(sz / (float)10), _max = sz / 2;
				printf(" (entre %d i %d):\n", _min, _max);
				ESBORRAR
				goto personalitzat;
			}
			ESBORRAR
			break;
		}
    // Comença el joc
		sz = cols * files;
		reiniciar_cells();
		primer_torn = 1;
		partida = JUGANT;
    
		clock_t antic = clock();
		while (partida == JUGANT) {
			system("cls");
			render();

			int x, y, flag = 0;
			
			while (!kbhit()) {
        // Cream un metrònom mentre no hagem d'escanejar res
				clock_t ara = clock();
				double div = (double)(ara - antic) / CLOCKS_PER_SEC;
				if (div - (int)div == 0) { // Per determinar si div és un enter
					antic = ara;
					while ((segons += div) >= 60) {
						segons -= 60;
						minuts++;
					}
					if (sz > 450) continue; // Evitar bloquejos al imprimir tant
					system("cls");
					render();
				}
			}

			scanf("%d", &x); // Escanejam el primer paràmetre

			if (x == -1) { // Si és -1, sortim del joc
				partida = MENU;
				break;
			}
			scanf("%d", &y);
			if (x == 0) { // Si el primer és 0, serà per marcar una casella i no per desvetllar-la
				flag = 1;
				x = y;
				scanf("%d", &y); // En tal cas, haurem d'escanejar un altre paràmetre més
			}

			if (x > cols || y > files || x < 1 || y < 1) continue;
			x--;
			y--;
			biuni(x, y); // resultat desat en la variable "pt" (camp[pt] és la casella desitjada)

			if (flag && (camp[pt].toString == BLANC || camp[pt].toString == 'f')) {
        // Marcarem o desmarcarem una casella
				if (camp[pt].bandera) {
					camp[pt].bandera = 0;
					camp[pt].toString = BLANC;
					banderes--;
				}
				else {
					camp[pt].bandera = 1;
					camp[pt].toString = 'f';
					banderes++;
				}
				flag = 0;
				primer_torn = 0;
				ESBORRAR
				continue; // Sortim del bucle
			}
			ESBORRAR
			if (primer_torn) { // Si és el primer torn i va i ens trobam una mina, canviam la distribució
				primer_torn = 0;
				while (camp[pt].bomba) reiniciar_cells();
			}
      // Mostram la cel·la
			camp[pt].bandera = 0;
			mostrar_cella(pt);
			destapar(pt);
			if (camp[pt].bomba) {
				// Hem perdut
				partida = PERDUT;
				for (int i = 0; i < sz; i++) mostrar_cella(i);
				break;
			}

			// Comprovam si guanyam:
			int guanyat = 1;
			for (int i = 0; i < sz; i++)
				if (!camp[i].bomba && camp[i].toString == BLANC) {
					guanyat = 0;
					break;
				}
			if (guanyat) partida = GUANYAT;
		}
		if (partida == MENU) continue;
		system("cls");
		render();

		switch (partida) { // Comprovam l'estat de la partida
		case GUANYAT:
			printf("\n\nMOLT BE! HAS GUANYAT!!");
			break;
		case PERDUT:
			printf("\n\nLLASTIMA! SORT PES PROPER PIC!");
			break;
		}
		_getch(); // Esperam a què presionem una tecla per continuar
	}
	return 0;
}
