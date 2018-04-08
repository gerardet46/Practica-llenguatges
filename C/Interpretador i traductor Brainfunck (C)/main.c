#pragma warning(disable : 4996)

#include <Windows.h> // Cancel·lar execució presionant ESC
#include <stdio.h> // printf(), scanf()...
// Segons el compilador se necessita <conio.h> (per usar _getch())

// Se poden canviar aquestes variables (millor hex que dec)
#define LIMIT 10000
#define BUFFER_SZ 4096 // Depèn de la consola, normalment admet introduir 4096 caràcters per input
#define LIMIT_BUCLE 100000
#define ESTRICTE 0x0 // 1 per evitar que una cel·la sobresurti de [0,255], millor 0, per compilar tots els codis
#define SZ_CH sizeof(char) // Per posar SZ_CH i no sizeof(char) tot el temps

#define ESC 0x1b // No canviar (ESC -> 27 (0x1b))

int ptr = 0x0; // Punter
int len = 0x0; // Llongitud del codi
char missatge[0x1f4]; // Missatge d'error
int* cells; // cel·les

typedef enum { PRINCIPAL, CELLS } RETURN; // Interpretació principal i de bucle
typedef enum { false, true } bool;

// Declaració de funcions
char* error(char* c);
int* interval(char* c);
bool interpretar(char* c, RETURN ret);
void html(char* c);

#pragma region Funcions de string
bool strpos(char* a, char c) { // Veure PHP
	for (int i = 0; i < strlen(a); i++)
		if (a[i] == c) return true;
	return false;
}
char* substr(char* s, int start, int end) { // Agafa un substring sabent l'index d'inici i de fi;
	char* n = malloc((end - start + 1) * SZ_CH);
	for (int i = 0; i < end - start + 1; i++) {
		n[i] = s[start + i];
		n[i + 1] = 0;
	}
	return n;
}
char* reverse(char* a) { // Veure PHP
	char n[100];
	for (int i = strlen(a) - 1; i >= 0; i--) n[i] = a[i];
	n[strlen(a)] = 0;
	return n;
}
char* to_string(int a) { // funció to_string(int), no existeix en C
	if (a == 0) return "0";
	if (a == 1) return "1";

	char n[100];
	int c = 0;
	while (a > 1) {
		n[c] = a % 10 + 48;
		c++;
		a /= 10;
	}
	n[c] = 0;
	return reverse(n);
}
#pragma endregion

int main() {
	while (true) {
		printf("Introduiex linees de codi BF\n- Per executar, escriu a una nova linea \"-exe\", per aturar execucio, presionar ESC)\n- Per compilar codi a Aplicacio Web (JavaScript), escriu \"-htm\":\n1: ");
		
		// Agafam primra línea de codi:
		char* codi = malloc(BUFFER_SZ * SZ_CH);
		gets(codi);
		len += strlen(codi);
		char a[BUFFER_SZ];
		
		// Agafam totes mentre no siguin "-exe" (executar) o "-htm" (pasar a JavaScript)
		int i = 0x1;
		while (++i) {
			printf("%i: ", i);		
			gets(a);

			if (a[4] == 0 && (strcmp(a, "-exe") == 0 || strcmp(a, "-htm") == 0)) break;

			len += strlen(a);

			char* b = malloc(len * SZ_CH);
			strcpy(b, codi);
			codi = realloc(b, len * SZ_CH);
			strcat(codi, a);
		}
		printf("\n");

		cells = malloc(LIMIT * sizeof *cells); // Resetejam les cel·les
		for (int i = 0; i < LIMIT; i++) cells[i] = 0;
		ptr = 0x0; // Resetejam el punter
		
		RETURN r;
		char* e = error(codi);
		if (e != "ok") printf("%s", e); // En cas d'error
		else if (strcmp(a, "-exe") == 0) { // Executar
			r = interpretar(codi, PRINCIPAL);
			if (!r) printf("\n\n-------------------------------\nEl programa ha acabat: %s", missatge); // Error en l'execució (no existeix "try-catch" en C)

			printf("\n\nDisposicio final de les 50 primeres cel.les:\n");
			for (int i = 0; i < 49; i++) printf("%i-", (int)cells[i]);
			printf("%i", (int)cells[50]);
		}
		else if (strcmp(a, "-htm") == 0) { // Traduir a HTML/JavaScript
			html(codi);
			printf("\nTraduccio a JavaScript correcte!");
			system("index.htm"); // Obre l'arxiu
		}
		_getch(); // Alguns compiladors necessitaran <conio.h>
		system("cls");
	}
	return 0;
}


bool interpretar(char* c, RETURN ret) {
	int* _int = interval(c); // Obtenim intervals principals
	int inte = 0x0;

	for (int i = 0; i < strlen(c); i++) {
		auto ch = c[i]; // Segons el compilador, usar "char" i no "auto"
		if (GetAsyncKeyState(ESC) && ch != ',') return false; // Si presionam ESC (27) <Windows.h>

		if (ch == '>') ++ptr;
		if (ch == '<') --ptr;
		if (ch == '+') {		
			if (ESTRICTE && cells[ptr] + 1 > 255) {
				strcpy(missatge, "\nError durant l'execucio: S'ha intentat asignar mes d'1 byte (255 en decimal) de memoria a la cel.la ");
				strcat(missatge, to_string(ptr + 1));
				return false; // error
			}
			++cells[ptr];
		}
		if (ch == '-') {
			if (ESTRICTE && cells[ptr] - 1 < 0) {
				strcpy(missatge, "\nError durant l'execucio: S'ha intentat asignar un valor negatiu a la cel.la ");
				strcat(missatge, to_string(ptr + 1));
				return false; // error
			}
			--cells[ptr];
		}
		if (ch == '.') printf("%c", (char)cells[ptr]);
		if (ch == ',') {
			printf("\nEsperant entrada de l'usuari: ");
			cells[ptr] = _getch();
		}
		if (ch == '[') { // Bucle
			i = _int[inte + 1]; // Obtenim quan acaba
			char* grup = substr(c, _int[inte] + 1, i); // Codi a interpretar dins el bucle

			int it = 0x0; // Limitam les iteracions (#define LIMIT_BUCLE)
			while (cells[ptr] != 0) { // Execució del bucle
				it++;
				if (it > LIMIT_BUCLE) {
					strcpy(missatge, "\nMassa iteracions d'un bucle.");
					return 0;
				}
				if (ptr < 0 || ptr >= LIMIT) {
					strcpy(missatge, "\nError durant l'execucio: Punter fora de l'interval.");
					return false;
				}
				bool re = interpretar(grup, CELLS); // Interpretam el que hi ha
				if (!re) return false; // En cas d'error, retornarem "false" per evitar que continuï l'execució (espècie de try-catch)
			}
			if (i >= strlen(c) - 1) break;
			inte += 2; // Anam eal proper bucle
		}
		if (ptr < 0 || ptr >= LIMIT) {
			strcpy(missatge, "\nError durant l'execucio: Punter fora de l'interval.");
			return false;
		}
	}
	if (ret == PRINCIPAL) printf("\n\n-------------------------------\nEl programa ha acabat satisfactoriament.");
	return true;
}

int* interval(char* c) { // Agafam els index de començament i final dels bulces principals d'un troç de codi (char* c)
	int* _int = malloc(strlen(c) * SZ_CH);
	int pos = 0, count = 0;

	if (!strpos(c, '[')) return _int;
	int a0;
	int niv = 0;

	for (int i = 0; i < strlen(c); i++) {
		char a = c[i];
		if (a == '[') {
			if (niv == 0) a0 = i;
			niv++;
		} if (a == ']') {
			niv--;
			if (niv == 0) {
				_int[count] = a0;
				_int[count + 1] = i;
				count += 2;
			}
		}
	}
	return _int;
}

void html(char* c) { // Escrivim a un arxiu .htm l'interpretació del codi amb JavaScript
	FILE* f = fopen("index.htm", "w+");
	fprintf(f, "<p id=\"res\"></p><script>let ptr=0,cells=[],it=0,m=null;\nfor(var i=0;i<10e5;i++)cells[i]=0;\nfunction cout(str){document.getElementById(\"res\").innerText+=str}\n");
	// Al ser un llenguatge lent i mostra els resultats al final, restringirem el nombre d'iteracions de bucle
	
	for (int i = 0; i < len; i++) {
		char q = c[i];
		if (q == '>') fprintf(f, "\nptr++;");
		if (q == '<') fprintf(f, "\nptr--;");
		if (q == '+') fprintf(f, "\ncells[ptr]++;");
		if (q == '-') fprintf(f, "\ncells[ptr]--;");
		if (q == '.') fprintf(f, "\ncout(String.fromCharCode(cells[ptr]));");
		if (q == ',') fprintf(f, "\nm=prompt(\"Indrodueix un caracter\");\ncells[ptr]=m.charCodeAt(0);");
		if (q == '[') fprintf(f, "\nwhile(cells[ptr]!=0&&(++it)<100000){");
		if (q == ']') fprintf(f, "\n}");
	}
	fprintf(f, "\n\ncout(\"\\n-----------------------------\\nEl programa ha acabat.\\n\\nDisposicio final de les primeres 50 cel.les:\\n\");for(let i=0;i<49;i++)cout(cells[i].toString()+'-');cout(cells[49].toString())</script>");
	fclose(f);
}

char* error(char* c) { // Comprovar si el nombre de '[' equival al nombre de ']'
	int nivell = 0;
	for (int i = 0; i < strlen(c); i++) {
		if (c[i] == '[') nivell++;
		if (c[i] == ']') nivell--;

		if (c[i] < 0) return "ok";
		if (nivell < 0) return "Vigila: massa tancaments de bucle";
	}
	if (nivell > 0) return "Vigila: bucle(s) sense tancar";
	return "ok";
}
