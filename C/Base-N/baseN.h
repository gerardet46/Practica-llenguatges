/*Implementació de HEX, BASE32 i BASE64 amb un únic mètode de convertir, i un altre per descodificar. Links per informar-se:
BASE32 -> 
BASE64 -> 
*/
#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>

// Caràcters referents (els iguals només són per afegir, però els possam per poder comprovar si un texte està ven codificat (amb iguals i tot)
#define BASE64 "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/="
#define BASE32 "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567="
#define HEX "0123456789abcdef"
#define ASCII "" // En realitat, els C tracta als ASCII com a números, per tant, només cal recordar que aquesta definició "és buida"

char* r, *r1, *temp, *temp2, plus[5] = ""; // Tots els punters que usarem (i un array), per evitar problemes de memòria

char* str_repat(char c, int n) { // Repetir un caràcter c n pics (str_repeat('A', 4) -> "AAAA")
	temp = malloc(n * sizeof(char));
	temp[n] = 0;
	for (int i = 0; i < n; i++) temp[i] = c;
	return temp;
}
char* _substr(char* t, int init, int l) { // Agafam la subcadena d'acord amb els paràmetres, com tots els altres llenguatges
	temp = malloc(l * strlen(t) * sizeof*t);
	for (int i = 0; i < l; i++) temp[i] = t[i + init];
	temp[l] = 0;
	return temp;
}
int indexof(char* t, char c) { // Donat un caràcter, tornam la primera vegada que apareix
	for (int i = 0; i < strlen(t); i++)
		if (t[i] == c) return i;
	return -1;
}

char* bin(int n, int bits) { // Convertim un nombre a binari (amb un cert nombre de bits)
	temp2 = malloc(bits * sizeof(char)); // Usam "temp2" perquè s'usarà dins la funció msg2bin, que ja fa feina amb el punter "temp"

	for (int i = 0; i < bits; i++) temp2[i] = '0'; // No usam str_repeat per evitar ambigüetats amb el punter "temp"
	temp2[bits] = 0;
	while (bits) {
		temp2[--bits] = ((n & 1) + 48); // Si l'últim digit és 1 (n & 1), tornarà el caràcter corresponent a 1 ('1' = 49), per això sumam 48
		n >>= 1;
	}
	return temp2;
}
int dec(char* bi) { // Mètode contrari, passam de binari a decimal
	int fact = 1, re = 0;
	for (int i = strlen(bi); i > 0; i--) {
		if (bi[i - 1] == '1') re += fact;
		fact *= 2;
	}
	return re;
}

// passam un texte sencer (t) a binari (caràcter a caràcter), amb un cert nombre de bits i aquí b és un dels abecedaris corresponents als que hem definit al principi
char* msg2bin(char* t, int bits, char* b) {
	temp = malloc(9 * sizeof* t);
	*temp = 0;
	for (int i = 0; i < strlen(t); i++) strcat(temp, bin(strcmp(b, "") == 0 ? t[i] : indexof(b, t[i]), bits)); // si b és buit, vol dir que usam ASCII, com he dit a la seva definició
	return temp;
}
/******************************************************************/
int verificar(char* t, char* v) { // Comprobam que tots els caràcters de t hi siguin a v (com una expressió regular)
	for (int i = 0; i < strlen(t); i++) if (indexof(v, t[i]) == -1) return 0;
	return 1;
}
// Mètode general per codificar:
/*
	t = texte
	val = abcedari corresponent (ASCII, HEX, BASE32, BASE64)
	inc = zeros a afegir per a cada '='
	log2_base = {BASE32 -> 5, BASE64 -> 6}
*/
char* enc(char* t, char* val, int inc, int log2_base) {
	if (strcmp(t, "") == 0) return ""; // Si el texte és en blanc, el tornam també en blanc
	strcpy(plus, ""); // plus seran els zeros que haurem d'afegir amb tal de que la llongitut entre el tamany dels troços sigui exacte

	char* a = msg2bin(t, 8, ASCII); // Tornam el texte a binari (l'usuari ha emprat ASCII)
	r = malloc(2 * strlen(t) * sizeof *t); // Si hi som al HEX, haurà el doble de caràcters (a BASE32 i 64 no són tants)
	int ind = -1;

	while (strlen(a) % log2_base) { // Mentre no sobri informació, afegim zeros d'acord amb el paràmetre inc
		strcat(plus, "="); // El texte codificat tindrà un '=' més al final
		strcat(a, str_repat('0', inc));
	}

	for (int i = 0; i < strlen(a); i += log2_base) { // Agafam troços de la llongitut que cal i els convertim al abecedari corresponent (val)
		char* c = _substr(a, i, log2_base);
		r[++ind] = val[dec(c)];
	}
	r[++ind] = 0; // indicam el final del texte
	return strcat(r, plus); // Retornam el texte i els iguals de més
}
// Mètode general per descodificar:
/*
	t = texte
	val = abcedari corresponent (ASCII, HEX, BASE32, BASE64)
	inc = zeros a afegir per a cada '='
	log2_base = {BASE32 -> 5, BASE64 -> 6}
*/
char* desc(char* t, char* val, int inc, int log2_base) {
	if (strcmp(t, "") == 0) return "";
	strcpy(plus, ""); // Resetejam el nombre d'iguals

	int x = strlen(t); // per no haver de cridar tot el temps a "strlen.asm"

	int pl = 0;
	while (t[x - 1] == '=') { // comprovam quants pics hem afegit '=' i els llevam
		pl += inc;
		temp2 = _substr(t, 0, --x);
		strcpy(t, temp2);
	}
	r1 = malloc(7 * x * sizeof* t); // Aquí guardarem el texte codificat en binari (no seran 8 bits)
	r = malloc(7 * x * sizeof* t); // I aquí el resultat
	// Convertim el missatge a binari
	r1 = msg2bin(t, log2_base, val);
	strcat(r1, str_repat('0', pl));

	// Convertim r1 (binari) a char* (agafant troços de 8 digits)
	for (int i = 0; i < strlen(r1); i += 8) r[i / 8] = (char)dec(_substr(r1, i, 8));
	r[strlen(r1) / 8] = 0; // Asignam el caràcter NULL per indicar el final de la cadena
	return r;
}
/******************************************************/
// Funcions de codificar
char* enc_hex(char* t) { return enc(t, HEX, 0, 4); }
char* enc_base32(char* t) { return enc(t, BASE32, 1, 5); }
char* enc_base64(char* t) { return enc(t, BASE64, 2, 6); }

// Funcions de descodificar
char* dec_hex(char* t) {
	return desc(t, HEX, 0, 4);
	// ALTERNATIVA (atès que al HEX mai no afegirem '=', ja que usa troços de 4 bits i no 8, i per tant és un divisor
	/*if (strcmp(t, "") == 0) return "";

	r = malloc(strlen(t) / 2 * sizeof *t);
	int ind = -1;

	for (int i = 0; i < strlen(t); i += 2) r[++ind] = indexof(HEX, t[i]) * 16 + indexof(HEX, t[i + 1]);
	r[++ind] = 0;
	return r;*/
}
char* dec_base32(char* t) { return desc(t, BASE32, 1, 5); }
char* dec_base64(char* t) { return desc(t, BASE64, 2, 6); }