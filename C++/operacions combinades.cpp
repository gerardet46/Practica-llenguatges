#include "gstring.h"

#include <conio.h>
#include <iostream>
#include <stdlib.h>
#include <stdexcept>
#include <Windows.h>
#include <sstream>
#include <fstream>
#include <math.h>
#include <regex>

#define COL_RESET 7
#define COL_RESULTAT 2
#define COL_ALERTA 6
#define COL_ERROR 12

#define CONSTANTS 3

USA_STR;

double redondeig(double x, int dec) {
	double fact = pow(10, dec);
	return floor((x * fact) + .5) / fact;
}

template<typename T1, typename T2>
class dicc {
public:
	vector<T1> nom;
	vector<T2> valor;
	int conta;

	void reset() {
		nom = vector<T1>();
		valor = vector<T2>();
		conta = 0;
	}

	void afegir(T1 n, T2 v) {
		nom.push_back(n);
		valor.push_back(v);
		conta++;
	}
	void afegir(pair<T1, T2> n) {
		nom.push_back(n.first);
		valor.push_back(n.second);
		conta++;
	}
	void afegir(pair<T1, T2> *n, int sz) {
		for (int i = 0; i < sz; i++) {
			auto x = n[i];
			afegir(x);
		}
	}
	void afegir(dicc<T1, T2> n) {
		for (int i = 0; i < n.conta; i++) {
			auto x = n[i];
			afegir(x);
		}
	}

	void set(int x, T1 val1, T2 val2) {
		nom[x] = val1;
		valor[x] = val2;
	}

	pair<T1, T2> operator[](int x) {
		pair<T1, T2> val = make_pair(nom[x], valor[x]);
		return val;
	}
	void operator=(const dicc<T1, T2>& d) {
		this->nom = d.nom;
		this->valor = d.valor;
		this->conta = d.conta;
	}
	dicc<T1, T2> operator+(const dicc<T1, T2>& a) const {
		dicc<T1, T2> r = *this;
		dicc<T1, T2> t = a;

		for (int i = 0; i < t.conta; i++) r.afegir(t[i]);
		return r;
	}
	dicc<T1, T2> operator+(pair<T1, T2> a) {
		dicc<T1, T2> r = *this;
		r.afegir(a);
		return r;
	}
	dicc<T1, T2> operator+=(const dicc<T1, T2>& a) const { return operator+(a); }
	void operator+=(pair<T1, T2> a) {
		this->afegir(a);
	}
	
	dicc() { reset(); }
};
template<typename T1, typename T2>
dicc<T1, T2> dicc_cast(pair<str, double> *t, int sz) {
	dicc<T1, T2> r;
	r.afegir(t, sz);
	return r;
}

void color(int c) {	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c); }

int max_nivell = 0;
int decimals = 4;
bool invalid = false, _error = false;

pair<str, double> constants[CONSTANTS] = {
	make_pair("pi", 3.1415926535897932384),
	make_pair("e", 2.7182818284590452353),
	make_pair("phi", 1.6180339887498948482)
};
dicc<str, double> variables;
dicc<str, double> tot;

int error(str op) {
	int nivell = 0;
	max_nivell = 0;
	for (auto c : op) {
		if (c == '(' && ++nivell > max_nivell) max_nivell = nivell;
		if (c == ')' && --nivell < 0) return -1;
	}
	return nivell;
	op = op + "?";
}

void signes(str &op) {
	while (op.find("-+") < op.length() || op.find("++") < op.length() || op.find("--") < op.length()) {
		str_replace(op, "-+", "-");
		str_replace(op, "++", "+");
		str_replace(op, "--", "+");
	}
	str_replace(op, "-", "+-");
	str_replace(op, "*+", "*");
	str_replace(op, "/+", "/");
	str_replace(op, 'x', '*');
	str_replace(op, ':', '/');
	str_replace(op, ")(", ")*(");
	if (començaAmb(op, "+")) op = substring(op, 1, op.length() - 1);
}
void _constants(str &op) {
	for (auto c : constants) {
		ostringstream os;
		os << c.second;
		str_replace(op, c.first, os.str());
	}
}

// Calcular operació sense parèntesis
double calcular(str op) {
	auto a = explode(op, "+");
	double r = 0;
	int pos1 = 0;
	dicc<str, double> trobat;

	bool torna = true;
	for (auto c : op) {
		if ((c < '0' || c > '9') && c != '.') {
			torna = false;
			break;
		}
	}
	if (torna) return stod(op);

	for (auto t : a) {
		for (int i = 0; i < 10; i++) {
			for (char c = 'a'; c <= 'z'; c++)
				str_replace(t, to_string(i) + c, to_string(i) + '*' + c);
			for (char c = 'A'; c <= 'Z'; c++)
				str_replace(t, to_string(i) + c, to_string(i) + '*' + c);
		}
		for (auto ch : t) {
			if (isalpha(ch)) {
				int max_length = 0;

				for (int i = 0; i < tot.conta; i++) {
					auto var = tot[i];
					if (var.first.length() > max_length) max_length = var.first.length();
				}
				while (1) {
					for (int i = 0; i < tot.conta; i++) {
						auto var = tot[i];
						if (var.first.length() == max_length && troba(t, var.first)) {
							regex rx("([a-zA-Z])(" + var.first + ")"), rx1("(" + var.first + ")([a-zA-Z])");
							if (regex_match(t, rx) || regex_match(t, rx1)) {
								invalid = true;
								return 0;
							}
							trobat += var;
						}
					}
					if (!(--max_length)) break;
				}
				break;
			}
		}

		auto b = explode(t, "*/");
		vector<double> bi = vector<double>();

		try {
			for (auto xb : b) {
				bool constant = false;
				for (int i = 0; i < trobat.conta; i++) {
					if (acabaAmb(xb, trobat[i].first)) {
						int pos = strpos(xb, trobat[i].first);
						str xb1 = substring(xb, 0, pos);
						str_replace(xb1, "-", "-1");

						bi.push_back(trobat[i].second * (xb1 == "" ? 1 : stod(xb1)));
						constant = true;
						break;
					}
				}
				if (!constant) bi.push_back(stod(xb));
			}
		}
		catch (const invalid_argument&) { invalid = true; return 0; }
		catch (const out_of_range&) { invalid = true; return 0; }

		double r_temp = bi[0], pos = 0;

		for (auto sg : t) {
			if (sg == '*') r_temp *= bi[++pos];
			else if (sg == '/') r_temp /= bi[++pos];
		}
		r += r_temp;
	}
	return r;
}

double calc(string op) {
	strtrim(op, ' ');
	signes(op);

	if (troba(op, "()")) {
		color(COL_ALERTA);
		cout << "Operacio invalidada per \"()\".\n\n";
		color(COL_RESET);
		_error = true;
		return 0;
	}
	for (int i = 0; i < 10; i++) {
		str n = to_string(i);
		str_replace(op, n + "(", n + "*(");
		str_replace(op, ")" + n, ")*" + n);
	}
	for (char i = 'a'; i < 'z'; i++) {
		str n = to_string(i);
		str_replace(op, n + "(", n + "*(");
		str_replace(op, ")" + n, ")*" + n);
	}
	for (char i = 'A'; i < 'Z'; i++) {
		str n = to_string(i);
		str_replace(op, n + "(", n + "*(");
		str_replace(op, ")" + n, ")*" + n);
	}

	int err = error(op);
	if (err > 0) {
		color(COL_ALERTA);
		cout << "Vigila: bucle sense tancar.\n\n";
		color(COL_RESET);
		_error = true;
		return 0;
	}
	if (err < 0) {
		color(COL_ALERTA);
		cout << "Vigila: massa tancaments de bucle.\n\n";
		color(COL_RESET);
		_error = true;
		return 0;
	}

	while (1) {
		if (!troba(op, ")") && !troba(op, ")")) {
			// Fora parèntesis
			double t = calcular(op);
			if (invalid) return 0;
			return calcular(op);
		}

		str_arr operacions = str_arr();
		str actual("");
		int nivell = 0;
		for (auto c : op) {
			if (c == '(' && ++nivell) continue;
			if (c == ')' && --nivell == max_nivell - 1) {
				operacions.push_back(actual);
				actual = "";
				continue;
			}
			if (nivell == max_nivell) actual += c;
		}
		for (int i = 0; i < operacions.size(); i++) {
			double resultat = calcular(operacions[i]);
			if (invalid) return 0;

			str_replace(op, "(" + operacions[i] + ")", to_string(resultat));
		}
		max_nivell--;
		signes(op);
	}
	return -1;
}

int main() {
	goto BUCLE;
__ERROR:
	color(COL_ERROR);
	cout << "Operacio no valida.\n\n";
	color(COL_RESET);
	invalid = false;
BUCLE:
	while (1) {
		ifstream arxiu("constants.txt");

		if (!arxiu) {
			ofstream _arxiu("constants.txt");
			_arxiu << "";
			_arxiu.close();
		}
		else {
			variables.reset();
			str linia;
			pair<str, double> *actual;
			while (getline(arxiu, linia)) {
				str_arr components = explode(linia, '=');
				variables.afegir(components[0], stod(components[1]));
			}
		}
		tot = variables + dicc_cast<str, double>(constants, CONSTANTS);
		arxiu.close();
		/////////////

		cout << ">> ";
	
		str op, temp_op = "";


		getline(cin, op);
		if (!op.length()) continue;
		temp_op = op;
		strtolower(temp_op);
		
		if (temp_op == "cls") {
			system("cls");
			continue;
		}
		else if (començaAmb(temp_op, "decimals ")) {
			op = substring(op, 9, op.length() - 9);
			decimals = floor(calc(op));

			if (decimals > 6) decimals = 6;
			if (decimals < 0) decimals = 0;

			color(COL_RESULTAT);
			cout << "Precisio decimal: " << decimals << "\n\n";
			color(COL_RESET);
		}
		else if (temp_op == "tancar") break;
		else if (temp_op == "supr_vars") {
			color(COL_ALERTA);
			cout << "Segur que vols esborrar totes les variables desades? (s = si, altre tecla=no): ";
			if (tolower(_getch()) == 's') {
				ofstream _arxiu("constants.txt");
				_arxiu << "";
				_arxiu.close();

				color(COL_RESULTAT);
				cout << "\n\nVariables esborrades";
			}
			color(COL_RESET);
			cout << "\n\n";
		}
		else if (començaAmb(temp_op, "supr ")) {
			op = substring(op, 5, op.length() - 5);
			strtrim(op, ' ');
			str linia, nou("");
			bool primera = true, trobada = false;

			ifstream arxiu("constants.txt");
			while (getline(arxiu, linia)) {
				str_arr components = explode(linia, '=');

				if (components[0] != op) {
					if (!primera) nou += "\n";
					else primera = false;
					nou += linia;
				}
				else trobada = true;
			}
			arxiu.close();

			ofstream _arxiu("constants.txt");
			_arxiu << nou;
			_arxiu.close();

			if (trobada) {
				color(COL_RESULTAT);
				cout << "Variable " << op << " esborrada\n\n";
			}
			else {
				color(COL_ALERTA);
				cout << "No s'ha trobat la variable " << op << "\n\n";
			}
			color(COL_RESET);
		}
		else if (troba(op, "=")) {
			while (troba(op, " =")) str_replace(op, " =", "=");
			while (començaAmb(op, " ")) op = substring(op, 1, op.length() - 1);
			auto s = explode(op, '=');

			bool errors = false;

			color(COL_ERROR);
			for (auto cons : constants) {
				if (cons.first == s[0]) {
					cout << "No es pot canviar el valor d'una constant (" << cons.first << " = " << cons.second << ").\n\n";
					errors = true;
					break;
				}
			}
			if (!errors && isdigit(s[0][0]) && (errors = true)) cout << "Les variables no poden comencar amb un digit.\n\n";
			if (!errors && troba(s[0], " ") && (errors = true)) cout << "Les variables no poden tenir espais.\n\n";
			if (!errors) for (auto c : s[0]) {
				if (!isdigit(c) && !isalpha(c)) {
					cout << "Les variables nomes poden tenir caracters alfanumerics.\n\n";
					errors = true;
					break;
				}
			}
			color(COL_RESET);
			if (!errors) {
				double val = calc(s[1]);
				if (invalid) goto __ERROR;
				if (_error && (_error = false)) continue;

				str linia, nou("");
				bool inserir = true, primera = true;

				ifstream arxiu("constants.txt");
				while (getline(arxiu, linia)) {
					str_arr components = explode(linia, '=');

					if (!primera) nou += "\n";
					else primera = false;

					if (inserir && components[0] == s[0] && !(inserir = false)) nou += components[0] + "=" + to_string(val);
					else nou += linia;
				}
				if (inserir) {
					if (!primera) nou += "\n";
					nou += s[0] + "=" + to_string(val);
				}
				arxiu.close();

				ofstream _arxiu("constants.txt");
				_arxiu << nou;
				_arxiu.close();

				color(COL_RESULTAT);
				cout <<  s[0] << " = " << redondeig(val, decimals) << "\n\n";
				color(COL_RESET);
			}
		}
		else {
			double val = calc(op);
			if (invalid) goto __ERROR;
			if (_error && !(_error = false)) continue;

			color(COL_RESULTAT);
			cout << "= " << redondeig(val, decimals) << "\n\n";
			color(COL_RESET);
		}
	}
	return 0;
}
