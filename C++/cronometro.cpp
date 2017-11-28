#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <stdlib.h>
#include <conio.h>

using namespace std;

int s,m,h;

string format_int(int a) {
    if (a > 9) return to_string(a);
    else return "0" + to_string(a);
}
string format_time(int a, int b, int c) {return format_int(a) + ":" + format_int(b) + ":" + format_int(c);}

string crono() {
    string r;
	system("cls");    
    s++;
    if (s == 60) {m++; s = 0;}
    if (m == 60) {h++; m = 0;}
    
    return format_time(h, m, s);
}
string tempo() {
    string r;
    system("cls");
    s--;
    if (s == -1) {m--; s = 59;}
    if (m == -1) {h--; m = 59;}

    return format_time(h, m, s);
}
int main() {	
    while (true) {
        h = 0; m = 0; s = 0;

        system("cls");
        cout << "1 => Cronometre\n2 => Temporitzador\n3 => Sortir\n";
        char a = getch();
        system("cls");

        if (a == '1') {
            cout << "00:00:00";
            while (true) {
                this_thread::sleep_for(chrono::seconds(1));
                cout << crono();
                if (kbhit()) break;
            }
        } else if (a == '2') {
            do {
                cout << "Segons: "; cin >> s;
                cout << "Minuts: "; cin >> m;
                cout << "Hores: "; cin >> h;
                system("cls");
            } while (s > 59 || m > 59 || s < 0 || m < 0);

            cout << format_time(h, m, s);
            while (true) {
                this_thread::sleep_for(chrono::seconds(1));
                cout << tempo();
                if (h == 0 && m == 0 && s == 0) {
                    cout << "\nHa acabat el temps (sortint en 4s)";
                    this_thread::sleep_for(chrono::seconds(4));
                    break;
                }
                if (kbhit()) break;
            }
        } else if (a == '3') break;
        else {
            system("cls");
            cout << "Entrada incorrecta";
            this_thread::sleep_for(chrono::milliseconds(1500));
        }
    }
    return 0;
}
