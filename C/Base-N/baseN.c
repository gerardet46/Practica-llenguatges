// Programa principal, demana a l'usuari fins que tanqui el programa un missatge i el tipus (HEX, BASE32, BASE64)

#pragma warning (disable : 4996)

// No olvidar incloure l'arxiu que ens permet fer totes les operacions
#include "baseN.h"

#define BUFF 4096 // Màxim de caràcters per agafar de l'usuari

char* gets(char* r) { return gets_s(r, BUFF); } // estandart de C (no és al compilador VC de Visual Studio)

int main() {
	char opt, mode, msg[BUFF], *r; // Declaració de variables
	// Bucle de l'aplicació
	while (1) {
		do { // Pregunta per quin tipus de codificació vol emprar
			printf("Selecciona:\n1 => HEX\n2 => BASE32\n3 => BASE64\n");
			opt = _getch();
			system("cls");
		} while (opt < '1' || opt > '3');

		do { // Ara el mateix per codificar/descodificar
			printf("Codificar o descodificar (1/2): ");
			mode = _getch();
			system("cls");
		} while (mode < '1' || mode > '2');

	missatge: // Si l'entrada no és vàlida (té caràcters no propis de cada tipus, tornarem a demanar pel missatge)
		printf("Escriu el missatge: ");
		gets(msg); // Agafam el missatge (usam gets() per poder obtenir els espais

		switch (opt) {
		case '1':
			if (!verificar(msg, HEX) && mode == '2') { // Si descodificam però l'entrada no és correcte
				printf("Entrada no valida\n");
				goto missatge; // Ens torna a demanar el missatge (és la forma més senzilla per fer-ho, com si fos una funció en Assembly)
			}
			r = mode == '1' ? enc_hex(msg) : dec_hex(msg);
			break;
		case '2':
			if (!verificar(msg, BASE32) && mode == '2') {
				printf("Entrada no valida\n");
				goto missatge;
			}
			r = mode == '1' ? enc_base32(msg) : dec_base32(msg);
			break;
		case'3':
			if (!verificar(msg, BASE64) && mode == '2') {
				printf("Entrada no valida\n");
				goto missatge;
			}
			r = mode == '1' ? enc_base64(msg) : dec_base64(msg);
			break;
		}
		printf("\nRESULTAT:\n%s", r); // Imprimim el resultat

		// Esperam que l'usuari presioni una tecla, i tornam a començar
		_getch();
		system("cls");
	}
	return 0;
}