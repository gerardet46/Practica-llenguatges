#include <iostream>
#include <string>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

using namespace std;

void clipboard(string a) {
	/*const char* b = a.c_str();
	const size_t len = strlen(b) + 1;
    HGLOBAL hMem =  GlobalAlloc(GMEM_MOVEABLE, len);
    memcpy(GlobalLock(hMem), b, len);
    GlobalUnlock(hMem);
    OpenClipboard(0);
    EmptyClipboard();
    SetClipboardData(CF_TEXT, hMem);
    CloseClipboard();*/
    HWND hwnd = ::GetActiveWindow();
    OpenClipboard(hwnd);
	EmptyClipboard();
	HGLOBAL hg=GlobalAlloc(GMEM_MOVEABLE,a.length()+1);
	if (!hg){
		CloseClipboard();
		return;
	}
	memcpy(GlobalLock(hg),a.c_str(),a.length()+1);
	GlobalUnlock(hg);
	SetClipboardData(CF_TEXT,hg);
	CloseClipboard();
	GlobalFree(hg);
}

int main(int argc, char const *argv[])
{
	srand(time(NULL));
	while (true) {
		system("cls");
		cout << "1 => Generar numero aleatori de x xifres\n2 => Sortir";
		char r = getch();

		system("cls");
		if (r == '1') {
			int num;
			cout << "Entra el numero de xifres: ";
			cin >> num;
			cout << (1 + rand() % 9);

			string r = "";
			for (int i = 1; i < num; i++) {
				int n = rand() % 10;
				cout << n;
				r += n;
			}
			cout << "\nNumero copiat";
			getch();
		} else if (r == '2') break;
	}
	return 0;
}
