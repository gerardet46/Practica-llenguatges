#pragma warning(disable : 4996)

#include <conio.h>
#include <stdlib.h>
#include <Windows.h>
#include <stdio.h>

// Se poden canviar aquestes variables
#define LIMIT 10000
#define BUFFER_SZ 4096
#define LIMIT_BUCLE 100000
#define ESTRICTE 0x0
#define SZ_CH sizeof(char)

#define ESC 0x1b // aquesta no

int ptr = 0x0;
int len = 0x0;
char missatge[0x1f4];
int* cells;

typedef enum { PRINCIPAL, CELLS } RETURN;
typedef enum { false, true } bool;

char* error(char* c);
int* interval(char* c);
bool interpretar(char* c, RETURN ret);
void html(char* c);

#pragma region Funcions de string
bool strpos(char* a, char c) {
	for (int i = 0; i < strlen(a); i++)
		if (a[i] == c) return true;
	return false;
}
char* substr(char* s, int start, int end) {
	char* n = malloc((end - start + 1) * SZ_CH);
	for (int i = 0; i < end - start + 1; i++) {
		n[i] = s[start + i];
		n[i + 1] = 0;
	}
	return n;
}
char* reverse(char* a) {
	char n[100];
	for (int i = strlen(a) - 1; i >= 0; i--) n[i] = a[i];
	n[strlen(a)] = 0;
	return n;
}
char* to_string(int a) {
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

		char* codi = malloc(BUFFER_SZ * SZ_CH);
		gets(codi);
		len += strlen(codi);
		char a[BUFFER_SZ];

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

		cells = malloc(LIMIT * sizeof *cells);
		for (int i = 0; i < LIMIT; i++) cells[i] = 0;
		ptr = 0x0;
		
		RETURN r;
		char* e = error(codi);
		if (e != "ok") printf("%s", e);
		else if (strcmp(a, "-exe") == 0) {
			r = interpretar(codi, PRINCIPAL);
			if (!r) printf("\n\n-------------------------------\nEl programa ha acabat: %s", missatge);

			printf("\n\nDisposicio final de les 50 primeres cel.les:\n");
			for (int i = 0; i < 49; i++) printf("%i-", (int)cells[i]);
			printf("%i", (int)cells[50]);
		}
		else if (strcmp(a, "-htm") == 0) {
			html(codi);
			printf("\nTraduccio a JavaScript correcte!");
			system("index.htm");
		}
		_getch();
		system("cls");
	}
	return 0;
}


bool interpretar(char* c, RETURN ret) {
	int* _int = interval(c);
	int inte = 0;

	for (int i = 0; i < strlen(c); i++) {
		auto ch = c[i];
		if (GetAsyncKeyState(ESC) && ch != ',') return false;

		if (ch == '>') ++ptr;
		if (ch == '<') --ptr;
		if (ch == '+') {		
			if (ESTRICTE && cells[ptr] + 1 > 255) {
				strcpy(missatge, "\nError durant l'execucio: S'ha intentat asignar mes d'1 byte (255 en decimal) de memoria a la cel.la ");
				strcat(missatge, to_string(ptr + 1));
				return false;
			}
			++cells[ptr];
		}
		if (ch == '-') {
			if (ESTRICTE && cells[ptr] - 1 < 0) {
				strcpy(missatge, "\nError durant l'execucio: S'ha intentat asignar un valor negatiu a la cel.la ");
				strcat(missatge, to_string(ptr + 1));
				return false;
			}
			--cells[ptr];
		}
		if (ch == '.') printf("%c", (char)cells[ptr]);
		if (ch == ',') {
			printf("\nEsperant entrada de l'usuari: ");
			cells[ptr] = _getch();
		}
		if (ch == '[') {
			i = _int[inte + 1];
			char* grup = substr(c, _int[inte] + 1, i);

			int it = 0;
			while (cells[ptr] != 0) {
				it++;
				if (it > LIMIT_BUCLE) {
					strcpy(missatge, "\nMassa iteracions d'un bucle.");
					return 0;
				}
				if (ptr < 0 || ptr >= LIMIT) {
					strcpy(missatge, "\nError durant l'execucio: Punter fora de l'interval.");
					return false;
				}
				bool re = interpretar(grup, CELLS);
				if (!re) return false;
			}
			if (i >= strlen(c) - 1) break;
			inte += 2;
		}
		if (ptr < 0 || ptr >= LIMIT) {
			strcpy(missatge, "\nError durant l'execucio: Punter fora de l'interval.");
			return false;
		}
		}
	if (ret == PRINCIPAL) printf("\n\n-------------------------------\nEl programa ha acabat satisfactoriament.");
	return true;
}

int* interval(char* c) {
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

void html(char* c) {
	FILE* f = fopen("index.htm", "w+");
	fprintf(f, "<p id=\"res\"></p><script>let ptr=0,cells=[],it=0,m=null;\nfor(var i=0;i<10e5;i++)cells[i]=0;\nfunction cout(str){document.getElementById(\"res\").innerText+=str}\n");

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

char* error(char* c) {
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