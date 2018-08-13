#pragma warning (disable : 4996)

/*
Programa per simplificar arrels quadrades (positives i negatives) en el rang de unsigned long long.
Sí, és unsigned per poder possar més nombres, però usam també unsigned pels negatius?

L'arrel quadrada de 12 (2·2·3) es pot expressar així "2·sqrt(3)" (traiem els quadrats de la factorització en factors
primers d'un nombre).

Fixau-vos que si és negatiu (-12), serà el mateix però de la forma "2i·sqrt(3)" (només afegim una i).
*/

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define UINT64_MAX "18446744073709551615" // Màxim unsigned long long en format string (2^64 - 1)

// 0 -> fals, 1 -> vertader
typedef unsigned long long uint64; // Acursar paraules

uint64 resultat[2], fact[64]; // uint64 = 2^64-1 (màxim 63 factors primers)
// resultat[0] -> radical, resultat[1] -> part que surt

uint64 __pow(uint64 a, int b) { // funció a ^ b (potència, no XOR) pels uint64
    if (!b) return 1;
    uint64 r = a;
    while (--b) r *= a;; // Multiplicam "a" b vegades
    return r;
}
// Nota: usam int i no bool perquè bool no és a C (clar que es pot definir):
// 1 = vertader, 0 = false;
int primer(uint64 n) {
    if (n == 2 || n == 3) return 1;
    if (!(n % 2) || !(n % 3)) return 0;

    int w = 4;
    // A partir de 5, només existeixen primers de la forma 6k + 1 ó 6k - 1
    for (uint64 i = 5; i * i <= n; i += w) {
        if (!(n % i)) return 0; // Si és divisible per i, no és primer
        w = 6 - w;
    }
    return 1;
}
void factoritzar(uint64 n) { // Factoritzam en factors primers
    /*
    Guardam la factorització en l'array fact, si és 12, seria [2,2,3]
    però en C no existeixen estructures dinàmiques, o sigui que hem de tenir en compte
    que el nombre de factor canvia. Per això, reservam el primer element de l'array per la compta
    de factor primers, o sigui que 50 seria així: [3 (n'hi ha 3), 2, 5, 5] (5x5x2=50)
    */
    int x = 0;
    for (uint64 i = 1; ; i += 2) { // Només pot haver-hi factors senars (llevat del 2);
        if (primer(n)) {
            fact[++x] = n;
            break;
        }
        if (n == 1) break;
        if (i == 1) i++; // Si el factor és 1, el canviam per 2
        if (!(n % i)) {
            // En cas de que sigui divisible, l'afegim i restam 2 al factor per veure si es repeteix
            fact[++x] = i;
            n /= i;
            if (i == 2) i -= 3;
            else i -= 2;
            continue;
        }
        if (i > 2 && i >= n / 2) {
            fact[++x] = n;
            n = 1;
            break;
        }
        if (i == 2) i--; // Si l'haviem canviat, el tornam a resetejar per avançar a 3,5,7,...
    }
    fact[0] = x; // El primer element és la compta de factors
}

uint64 toUINT64(char* s) { // Convertim un char* a uint64
    uint64 r = 0, det = 1;
    for (int i = strlen(s) - 1; i >= 0; i--) {
        if (i == 0 && *s == '-') break; // Si és negatiu, ignoram el signe (ja que és unsigned long long)
        r += (s[i] - 48) * det;
        det *= 10;
    }
    return r;
}
void simplificar(uint64 x) {
    // PRIMER ALGORISME PENSAT (si l'actual tarda 3 segons, aquest tarda 2 minuts!!)
    /*resultat[0] = x;
    uint64* a = &resultat[0];
    while (!primer(*a) && *a > 1) {
        int br = 1;
        for (uint64 i = 2; i < *a; i++)
            if (!(*a % i) && !((*a / i) % i)) {
                *a /= i * i;
                resultat[1] *= i;
                br = 0;
            }
        if (br) break;
    }*/
    resultat[0] = resultat[1] = 1; // Resetejam els resultats

    printf("Factoritzant...\n"); // Assenyalam a l'usuari que esteim factoritzant el nombre
    factoritzar(x);
    printf("Fet (%d factors primers [total])\nSimplificant arrel...\n\n", fact[0]);

    for (int i = 1; i <= fact[0];) { // La i no avançarà
        int x = i;
        uint64 actual = fact[i];
        while (actual == fact[++x]); // Comprovam quants pics es repeteixen els factors (ja que estan en ordre)
        x -= i; // Nombre de factors repetits (si és parell, els traeim tots, sinó ens quedarà un a l'arrel)
        resultat[1] *= __pow(actual, x / 2); // Treim la meitat dels factors repetits (sqrt(2^6) = 2^3 = 8) (C fa un floor automàtic en cas de que x sigui senar)
        if (x % 2) resultat[0] *= actual; // Si x és senar, en quedarà un
        i += x; // Avançam la i una variable interna, per això no ho possam adalt
    }
}

int ver_numero(char* n) { // Verificam si la cadena té un format correcte numèric sencer
    int st = 0;
    if (*n == '-') st++; // En cas de que sigui negatiu, l'ignoram (avançam 1 a l'index)
    for (int i = st; i < strlen(n); i++)
        if (n[i] > '9' || n[i] < '0') return 0; // Si no és un caràcter numèric, tornam fals;
    return 1;
}
int tamany_num(char* s) { // Comprovam que el número (en format de cadena, hi sigui a l'interval 2^64 < x < 2^64)
    char n[21]; // 2 ^ 64 - 1 té 20 digits
    if (*s == '-') { // Si és negatiu, ignoram el signe
        for (int i = 1; i < strlen(s); i++) {
            n[i - 1] = s[i];
            n[i] = 0;
        }
    } else strcpy(n, s); // En cas de positiu, n serà igual
    if (strlen(n) > 20) return 0; // Si té més xifres que del permès, torna fals
    if (strlen(n) < 20) return 1; // Si, per contra, en té menys, serà menor

    // En cas de que hagi les mateixes xifres
    for (int i = 0; i < strlen(n); i++) {
        if (n[i] > UINT64_MAX[i]) return 0;
        if (n[i] < UINT64_MAX[i]) return 1;
        // Continuarà el bucle si les xifres concideixen
    }
    return 1;
}
// Punt d'entrada
int main() {
    while (1) {
        char inp[64];
        uint64 n;
        int negatiu = 0;
        // Començament del programa

demanar:
        printf("Escriu el numero per simplificar la seva arrel (pot ser negatiu): ");
        scanf("%s", &inp); // Escanejam com cadena per comprovam l'interval, el signe i el format
        if (!ver_numero(inp)) { // Si no té el format correcte
            printf("Format incorrecte, vigila que sigui un enter.\n\n");
            goto demanar; // Torna a demanar el número
        }
        if (!tamany_num(inp)) { // Si no hi és a l'interval
            printf("Nombre fora d'interval (ha de ser a l'interval -2^64 < x < 2^64).\n\n");
            goto demanar;
        }
        if (*inp == '-') negatiu = 1; // En cas de ser negatiu
        n = toUINT64(inp); // ATENCIÓ: Aquesta funció ignora el signe
        if (n < 2) { // n=0, n=1
            // Imprimim el resultat (sqrt(n) = n, amb n dins {0, 1} i ens botam l'execució)
            if (negatiu && n) printf("sqrt(-1) = i");
            //else printf("sqrt(%d) = %d", n, n);
            else {
                printf("sqrt(%d) = ", n);
                printf("%d", n);
            }
            goto final;
        }
        clock_t begin = clock(); // Mesurarem el temps que tarda
        simplificar(n); // Cridam a la funció principal
        clock_t end = clock();

        // Imprimim el resultat ("%llu" és per unsigned long long)
        printf("--------------\nsqrt(%s) = ", inp);
        if (resultat[1] > 1) printf("%llu", resultat[1]);
        if (negatiu) printf("i"); // Si el resultat és complexe, imprimim "i" (sqrt(-1))
        if ((resultat[1] > 1 && resultat[0] > 1) || (negatiu && resultat[0] > 1)) printf(" * ");
        if (resultat[0] > 1) printf("sqrt(%llu)", resultat[0]);
        printf("\n\nCompletat en %d ms", (1000 * (end - begin) / CLOCKS_PER_SEC));
final:
        // Esperam l'entrada de l'usuari i tornam a començar
        getch();
        system("cls");
    }
    return 0x0;
}
