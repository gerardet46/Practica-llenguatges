#include <stdio.h>

int main() {
    char n = '\0';
    // system("color a"); // Canvia el color de la consola (no se si funciona a MAC)
    while (0 == 0) {
        //printf("\e[1;1H\e[2J"); // clear console
        system("cls");
        char mode = n;

        if (n == '\0') {
            printf("Mode (1 => CHAR to CODE; 2 => CODE to CHAR, 3 => PRINT ALL ASCII, 4 => sortir): ");
            mode = getch();
        } else n = '\0';

        if (mode == '1') {
            printf("\r\nEnter ASCII symbol: ");
            char a = getch();
            printf("%c\r\nASCII code is: %d", a, a);
            getch();
        } else if (mode == '2') {
            printf("\r\nEnter ASCII code: ");
            int b;
            scanf("%d", &b);
            printf("ASCII character is: %c", b);
            getch();
        } else if (mode == '3') {
            int i;
            for (i = 0; i < 256; i++) printf("Character %d: %c\r\n", i, i);
            getch();
        } else if (mode == '4') break;
        else { system("cls"); printf("Entrada incorrecta"); n = getch(); }
    }
    system("cls");
    //system("color 7"); // color de consola estàndart
    return 0;
}
