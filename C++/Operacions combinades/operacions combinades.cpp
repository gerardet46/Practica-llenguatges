#include "gstring.h"
#include "conjunts.h"

#include <conio.h>
#include <iostream>
#include <stdlib.h>
#include <stdexcept>
#include <sstream>
#include <fstream>
#include <math.h>
#include <regex>

#ifdef _WIN32
#include <Windows.h>

#define COL_RESET 7
#define COL_RESULTAT 2
#define COL_ALERTA 6
#define COL_ERROR 12
#else
#define COL_RESET "\x1b[0m"
#define COL_RESULTAT "\x1b[32m"
#define COL_ALERTA "\x1b[33m"
#define COL_ERROR "\x1b[31m"
#endif

#define CONSTANTS 4

USA_STR;

// Redondejar números
double redondeig(double x, int dec) {
	double fact = pow(10, dec);
	return floor((x * fact) + .5) / fact;
}

// Canviar el color de la consola de manera més escurçada
#ifdef _WIN32
void color(int c) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c); }
#else
void color(char* c) { cout << c; }
#endif

// Variables globals (pensava que n'hauria més, jeje)
int max_nivell = 0;
int decimals = 6;

// Constants, se poden afegir-ne més
pair<str, double> constants[CONSTANTS] = {
	make_pair("pi", 3.1415926535897932384),
	make_pair("tau", 6.283185307179586476),
	make_pair("e", 2.7182818284590452353),
	make_pair("phi", 1.6180339887498948482)
};
// Per qualque cosa he creat la classe "dicc" a l'arxiu "conjunts.h"
dicc<str, double> variables;
dicc<str, double> tot;
dicc<str, conjunt> conjunts;
dicc<str, double(*)(double)> funcio;
dicc<str, str> funcions_per;
vector<double> historial;

int func_length = 0;

// Comprovar si falten o sobren parèntesis
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

// Mètode per substituir signes repetits (cal tenir en comte que separam les operacions únicament per '+', no per '-')
void signes(str &op) {
	while (op.find("-+") < op.length() || op.find("++") < op.length() || op.find("--") < op.length()) {
		str_replace(op, "-+", "-");
		str_replace(op, "++", "+");
		str_replace(op, "--", "+");
	}
	str_replace(op, "-", "+-");
	str_replace(op, "*+", "*");
	str_replace(op, "/+", "/");
	str_replace(op, ")(", ")*(");
	if (començaAmb(op, "+")) op = substring(op, 1, op.length() - 1);
}
// Subtituim les constants d'una operacio
void _constants(str &op) {
	for (auto c : constants) {
		ostringstream os;
		os << c.second;
		str_replace(op, c.first, os.str());
	}
}
// Mètode especialitzat pels conjunts
void _conjunts(str &op) {
	int nivell = 0;
	str txt("");
	for (auto c : op) {
		if (c == '[') nivell++;
		else if (c == ']' && !(--nivell)) {
			double r = calc(txt);
			if (invalid || _error) return;

			int k = (int)r;
			if ((double)k == r)	str_replace(op, '[' + txt + ']', '[' + to_string(k) + ']');
			else {
				color(COL_ALERTA);
				cout << "L'index del conjunt ha de ser sencer (actual " << r << ").\n\n";
				color(COL_RESET);
				_error = true;
				return;
			}
		}
		else if (nivell) txt += c;
	}
	if (nivell > 0) {
		color(COL_ALERTA);
		cout << "Falten ']'.\n\n";
		color(COL_RESET);
	}
	if (nivell < 0) {
		color(COL_ALERTA);
		cout << "Sobren ']'.\n\n";
		color(COL_RESET);
	}
}

// Calcular operació sense parèntesis
double calcular(str op) {
	auto a = explode(op, "+"); // Separam l'operació pel signe '+'
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
		for (int i = 0; i < 11; i++) {
			if (i < 10) {
				for (char c = 'a'; c <= 'z'; c++)
					str_replace(t, to_string(i) + c, to_string(i) + '*' + c);
				for (char c = 'A'; c <= 'Z'; c++)
					str_replace(t, to_string(i) + c, to_string(i) + '*' + c);
			} else {
				str_replace(t, "](", "]*(");
			}
		}
		// historial
		for (int i = 1; i <= 10; i++) {
			if (troba(t, "ans[" + to_string(i) + "]")) {
				str_replace(t, "ans[" + to_string(i) + "]", to_string(historial[i - 1]));
			}
		}
		// variables
		for (auto ch : t) {
			if (isalpha(ch)) {
				int max_length = 0;

				for (int i = 0; i < tot.compte; i++) {
					auto var = tot[i];
					if (var.first.length() > max_length) max_length = var.first.length();
				}
				for (int i = 0; i < conjunts.compte; i++) {
					auto var = conjunts[i];
					if (var.first.length() > max_length) max_length = var.first.length();
				}
				while (1) {
					// Per als conjunts
					for (int i = 0; i < conjunts.compte; i++) {
						auto var = conjunts[i];
						if (var.first.length() == max_length && troba(t, var.first + "[")) {
							regex rx("([a-zA-Z])(" + var.first + ")");
							if (regex_match(t, rx)) {
								invalid = true;
								return 0;
							}
							rx = regex(var.first + "\\[(\\-?[0-9]+)\\]");
							smatch matches;
							if (regex_search(t, matches, rx)) {
								int ind = stoi(matches[1]);
								if (ind > conjunts[i].second.sz() || ind <= 0) {
									color(COL_ALERTA);
									cout << "L'index del conjunt \"" << var.first << "\" es fora d'interval.\n\n";
									color(COL_RESET);
									_error = true;
									return 0;
								}
								trobat.afegir(var.first + "[" + (str)(matches[1]) + "]", conjunts[i].second[ind]);
							}
						}
					}
					// Per a les variables
					for (int i = 0; i < tot.compte; i++) {
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
			
		auto b = explode(t, "*/%");
		vector<double> bi = vector<double>();
		// Fem les multiplicacions i divisions de cada terme i les sumam, que serà el resultat
		try {
			for (auto xb : b) {
				bool constant = false;
				for (int i = 0; i < trobat.compte; i++) {
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
			else if (sg == '%') r_temp = (int)r_temp % (int)bi[++pos];
		}
		r += r_temp;
	}
	return r;
}
// El mateix però per operacions més complexes (sempre recurrirà a la funció simplificada per fer els càlculs)
double calc(string op) {
	str_replace(op, "mod", "%");
	strtrim(op, ' ');
	signes(op);
	_conjunts(op);
	if (_error || invalid) return 0;

	if (strpos(op, '(')) {
		for (char c = 'a'; c <= 'z'; c++) {
			str_replace(op, ")" + to_string(c), ")*" + to_string(c));
			for (int i = 0; i < 10; i++)
				str_replace(op, to_string(i) + c, to_string(i) + '*' + c);
		}

		int max_func = 1;
		for (int i = 0; i < funcions_per.compte; i++)
			if (funcions_per[i].first.length() > max_func)
				max_func = funcions_per[i].first.length();

		while (--max_func + 1) for (int i = 0; i < funcions_per.compte; i++) {
			if (funcions_per[i].first.length() != max_func + 1) continue;
			int pos = strpos(op, funcions_per[i].first + "(");
			if (pos >= 0) {
				int nivell = 1;
				str _op = "";
				for (int j = pos + funcions_per[i].first.length() + 1; j < op.length(); j++) {
					if (op[j] == '(') nivell++;
					else if (op[j] == ')' && --nivell == 0) break;
					_op += op[j];
				}
				if (nivell) goto __ERROR;
				tot += make_pair("x", calc(_op));

				double val = calc(funcions_per[i].second);
				str_replace(op, funcions_per[i].first + "(" + _op + ")", to_string(val));
				tot.esborrar("x");
				i--;
			}
		}
	}
	goto __NO_ERROR;
__ERROR:
	color(COL_ERROR);
	cout << "L'argument de la funcio no s'ha tancat.\n\n";
	color(COL_RESET);
	_error = true;
	return 0;

__NO_ERROR:
	if (troba(op, "()")) {
		color(COL_ERROR);
		cout << "Operacio invalidada per \"()\".\n\n";
		color(COL_RESET);
		_error = true;
		return 0;
	}
	if (troba(op, "[]")) {
		color(COL_ERROR);
		cout << "Operacio invalidada per \"[]\".\n\n";
		color(COL_RESET);
		_error = true;
		return 0;
	}

	// Cercam si trobam qualque funció a l'operació
	int f_length = func_length + 1;
	while (--f_length) {
		for (int i = 0; i < funcio.compte; i++) {
			if (funcio[i].first.length() != f_length) continue;

			int pos = strpos(op, funcio[i].first + "(");
			if (pos >= 0) {
				int nivell = 1;
				str oper("");
				pos += funcio[i].first.length();

				while (++pos) {
					if (op[pos] == '(') nivell++;
					else if (op[pos] == ')') nivell--;
					if (!nivell) break;

					oper += op[pos];
				}
				if (nivell) goto __ERROR;
				double val = calc(oper);
				if (_error || invalid) return 0;
				str_replace(op, funcio[i].first + "(" + oper, "(" + to_string(funcio[i].second(val)));
			}
		}
	}

	// Fem qualcunes substitucions
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
	// Revisam si falten o sobren parèntesis
	int err = error(op);
	if (err > 0) {
		color(COL_ALERTA);
		cout << "Vigila: exces de '('.\n\n";
		color(COL_RESET);
		_error = true;
		return 0;
	}
	if (err < 0) {
		color(COL_ALERTA);
		cout << "Vigila: exces de ')'.\n\n";
		color(COL_RESET);
		_error = true;
		return 0;
	}
	// Elevat (a^b)
	int ind = strpos(op, '^');
	str primer(""), segon("");
	if (ind > 0) {
		// Calcular la base
		if (op[ind - 1] == ')') {
			int k = ind - 1, nivell = 1;
			primer = ")";
			while (nivell && --k >= -1) {
				if (k == -1) {
					color(COL_ERROR);
					cout << "Operacio invalida.\n\n";
					color(COL_RESET);
					_error = true;
					return 0;
				}
				primer = op[k] + primer;

				if (op[k] == '(') nivell--;
				else if (op[k] == ')') nivell++;
			}
		}
		else {
			int k = ind;
			while (--k >= 0 && (isalnum(op[k]) || op[k] == '.')) {
				primer = op[k] + primer;
			}
		}

		// Calcular l'exponent
		if (op[ind + 1] == '(') {
			int k = ind + 1, nivell = 1;
			segon = "(";
			while (nivell && ++k <= op.length()) {
				if (k == op.length()) {
					color(COL_ERROR);
					cout << "Operacio invalida.\n\n";
					color(COL_RESET);
					_error = true;
					return 0;
				}
				segon += op[k];

				if (op[k] == '(') nivell++;
				else if (op[k] == ')') nivell--;
			}
		}
		else {
			int k = ind;
			while (++k < op.length() && (isalnum(op[k]) || op[k] == '.')) {
				segon += op[k];
			}
		}
		str_replace(op, primer + "^" + segon, to_string(pow(calc(primer), calc(segon))));
		return calc(op);
	}
	// Factorial (x! = gamma(n + 1))
	ind = strpos(op, '!');
	str terme("");
	if (ind > 0) {
		// Calcular la base
		if (op[ind - 1] == ')') {
			int k = ind - 1, nivell = 1;
			terme = ")";
			while (nivell && --k >= -1) {
				if (k == -1) {
					color(COL_ERROR);
					cout << "Operacio invalida.\n\n";
					color(COL_RESET);
					_error = true;
					return 0;
				}
				terme = op[k] + terme;

				if (op[k] == '(') nivell--;
				else if (op[k] == ')') nivell++;
			}
		}
		else {
			int k = ind;
			while (--k >= 0 && (isalnum(op[k]) || op[k] == '.')) {
				terme = op[k] + terme;
			}
		}
		// Re-emplaaçar
		double v = tgamma(calc(terme) + 1);
		str_replace(op, terme + "!", to_string(v));
		return calc(op);
	}

	// Mentre no s'acabi l'operació, anirem agafant els parèntesis més interiors i executant-los per parts,
	// aprofintant la funció calcular()
	while (1) {
		if (!troba(op, ")") && !troba(op, ")")) {
			// Fora parèntesis
			double t = calcular(op);
			if (invalid || _error) return 0;
			return t;
		}
		// Separam les operacions simples a fer (seleccionam les que no tenguin parèntesis)
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
			if (invalid || _error) return 0;

			str_replace(op, "(" + operacions[i] + ")", to_string(resultat));
		}
		max_nivell--;
		signes(op);
	}
	return -1;
}

double csc(double x) { return 1 / sin(x); }
double sec(double x) { return 1 / cos(x); }
double cot(double x) { return 1 / tan(x); }
double sgn(double x) { return x < 0 ? -1 : (x == 0 ? 0 : 1); }

#define DEG_RAD(x) (x * 3.1415926535897932384 / 180)
#define RAD_DEG(x) (x * 180 / 3.1415926535897932384)

double _sin(double x) { return sin(DEG_RAD(x)); }
double _cos(double x) { return cos(DEG_RAD(x)); }
double _tan(double x) { return tan(DEG_RAD(x)); }

double _csc(double x) { return 1 / sin(DEG_RAD(x)); }
double _sec(double x) { return 1 / cos(DEG_RAD(x)); }
double _cot(double x) { return 1 / tan(DEG_RAD(x)); }

double _asin(double x) { return RAD_DEG(asin(x)); }
double _acos(double x) { return RAD_DEG(acos(x)); }
double _atan(double x) { return RAD_DEG(atan(x)); }
double frac(double x) { return x - floor(x); }

int main() {
	// Afegim les funcions principals de les calculadores (ln, sin, cos, ...)
	funcio.afegir("ln", log);
	funcio.afegir("log", log10);
	funcio.afegir("gamma", tgamma);

	funcio.afegir("sqrt", sqrt);

	funcio.afegir("abs", abs);
	funcio.afegir("sgn", sgn);
	funcio.afegir("floor", floor);
	funcio.afegir("ceil", ceil);
	funcio.afegir("frac", frac);

	funcio.afegir("sin", sin);
	funcio.afegir("cos", cos);
	funcio.afegir("tan", tan);
	funcio.afegir("csc", csc);
	funcio.afegir("sec", sec);
	funcio.afegir("cot", cot);

	funcio.afegir("asin", asin);
	funcio.afegir("acos", acos);
	funcio.afegir("atan", atan);

	funcio.afegir("_sin", _sin);
	funcio.afegir("_cos", _cos);
	funcio.afegir("_tan", _tan);
	funcio.afegir("_csc", _csc);
	funcio.afegir("_sec", _sec);
	funcio.afegir("_cot", _cot);

	funcio.afegir("_asin", _asin);
	funcio.afegir("_acos", _acos);
	funcio.afegir("_atan", _atan);

	func_length = 0;
	for (int i = 0; i < funcio.compte; i++) {
		if (funcio[i].first.length() > func_length)
			func_length = funcio[i].first.length();
	}
	
	goto BUCLE;
__ERROR:
	color(COL_ERROR);
	cout << "Operacio no valida.\n\n";
	color(COL_RESET);
	invalid = false;
BUCLE:
	while (1) {
		// Cada cop que demanam per fer qualque cosa, actualitzarem totes les variables i l'historial
		ifstream arxiu("constants.txt");

		dicc<str, str> conj;
		if (!arxiu) {
			ofstream _arxiu("constants.txt");
			_arxiu << "";
			_arxiu.close();
		}
		else {
			variables.reset();
			conjunts.reset();
			funcions_per.reset();
			str linia;
			
			while (getline(arxiu, linia)) {
				str_arr components = explode(linia, '=');
				if (components[1][0] == '{')
					conj.afegir(components[0], components[1]);
				else if (troba(components[0], "(x)")) {
					strtrim(components[0], "(x)");
					funcions_per.afegir(components[0], components[1]);
				}
				else
					variables.afegir(components[0], stod(components[1]));
			}
		}
		tot = variables + dicc_cast<str, double>(constants, CONSTANTS);
		for (int i = 0; i < conj.compte; i++) {
			conjunt t = conjunt(conj[i].second);
			conjunts.afegir(conj[i].first, t);
		}
		arxiu.close();

		arxiu = ifstream("historial.txt");
		if (!arxiu) {
			ofstream _arxiu("historial.txt");
			_arxiu << "";
			_arxiu.close();
		}
		else {
			historial = vector<double>();
			str linia;
			while (getline(arxiu, linia)) historial.push_back(stod(linia));
		}
		arxiu.close();
		/////////////

		cout << ">> ";
		str op, temp_op = "";
		// Demanam un comand a l'usuari

		getline(cin, op);
		if (!op.length()) continue;
		temp_op = op;
		strtolower(temp_op);
		
		if (temp_op == "cls") { // esborram la pantalla
			system("cls");
			continue;
		}
		else if (començaAmb(temp_op, "decimals ")) { // adjustar la presició decimal
			op = substring(op, 9, op.length() - 9);
			decimals = stoi(op);

			if (decimals > 6) decimals = 6;
			if (decimals < 0) decimals = 0;

			color(COL_RESULTAT);
			cout << "Precisio decimal: " << decimals << "\n\n";
			color(COL_RESET);
		}
		else if (temp_op == "tancar") break; // Acaba el programa
		else if (temp_op == "ans") { // Accedim a l'historial (recordem que és un conjunt)
			int i = 0;
			for (auto x : historial) {
				cout << "ans[" << ++i << "] = " << x << "\n";
			}
			cout << "\n";
		}
		else if (temp_op == "funcs") { // Per veure totes les funcions que tenim a disposició
			for (int i = 0; i < funcio.compte; i++)
				cout << funcio[i].first << "\n";
			cout << "\n";
			for (int i = 0; i < funcions_per.compte; i++) {
				cout << funcions_per[i].first << "(x) = " << funcions_per[i].second << "\n";
			}
		}
		else if (temp_op == "vars") { // El mateix per a les variables
			for (int i = 0; i < variables.compte; i++) {
				cout << variables[i].first << " = " << variables[i].second << "\n";
			}
			cout << "\n";
			for (int i = 0; i < conjunts.compte; i++) {
				cout << conjunts[i].first << " = " << conjunts[i].second.toString() << "\n";
			}
			cout << "\n";
		}
		else if (temp_op == "consts") {
			for (int i = 0; i < CONSTANTS; i++) {
				cout << constants[i].first << " = " << constants[i].second << "\n";
			}
			cout << "\n";
		}
		else if (temp_op == "?") { // Una mica d'ajut a l'usuari mai no va malament
			cout << "supr [nom_variable / nom_funcio(x)] -> esborra variable/funcio\n";
			cout << "supr_vars -> esborra variables i funcions\n";
			cout << "[nom_variable] = /expresio matematica/ -> assignar variable\n";
			cout << "[nom_conjunt] = {expr1, expr2, expr3, ...} -> assignar conjunt\n";
			cout << "[nom_funcio](x) = expressio matematica (x es la variable) -> assignar funcio\n";
			cout << "a[n] -> conjunt a, index n\n";
			cout << "consts -> mostra les constants\n";
			cout << "vars -> mostra les variables i els conjunts\n";
			cout << "funcs -> mostra les funcions\n";
			cout << "expr1 == expr2 -> comproba si expr1 = expr2\n";
			cout << "expr1 >= expr2 -> comproba si expr1 >= expr2\n";
			cout << "expr1 <= expr2 -> comproba si expr1 <= expr2\n";
			cout << "expr1 > expr2 -> comproba si expr1 > expr2\n";
			cout << "expr1 < expr2 -> comproba si expr1 < expr2\n";
			cout << "decimals n -> ajustar precisio amb n decimals\n";
			cout << "cls -> esborra la pantalla\n";
			cout << "tancar -> tanca el programa\n";
			cout << "ans = {ans[1], ans[2], ..., ans[10]} -> conjunt dels 10 darrers resultats\n";

			cout << "\n";
		}
		else if (temp_op == "supr_vars") { // Esborram totes les varialbes i les funcions
			color(COL_ALERTA);
			cout << "Segur que vols esborrar totes les variables/funcions desades? (s = si, altre tecla=no): ";
			if (tolower(_getch()) == 's') {
				ofstream _arxiu("constants.txt");
				_arxiu << "";
				_arxiu.close();

				color(COL_RESULTAT);
				cout << "\n\nVariables/funcions esborrades";
			}
			color(COL_RESET);
			cout << "\n\n";
		}
		else if (començaAmb(temp_op, "supr ")) { // Esborram una en particular
			op = substring(op, 5, op.length() - 5);
			strtrim(op, ' ');
			str linia, nou("");
			bool primera = true, trobada = false;

			arxiu = ifstream("constants.txt");
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
				cout << "Variable/funcio " << op << " esborrada\n\n";
			}
			else {
				color(COL_ERROR);
				cout << "No s'ha trobat la variable/funcio " << op << "\n\n";
			}
			color(COL_RESET);
		}
		else if (troba(op, "+=") || troba(op, "-=") || troba(op, "/=") || troba(op, "*=")) {
			// Aplicat als conjunts i a les variables
			char chr = '+';
			if (troba(op, "-=")) chr = '-';
			else if (troba(op, "*=")) chr = '*';
			else if (troba(op, "/=")) chr = '/';

			auto s = explode(op, to_string(chr) + "=");
			bool trobat = false;
			regex rx("^([a-zA-Z]+)\\[(.+)\\]$");
			
			if (regex_match(s[0], rx)) {
				smatch res;
				regex_search(s[0], res, rx);

				for (int i = 0; i < conjunts.compte; i++) {
					if (res[1] == conjunts[i].first) {
						double val1 = calc(res[2]), val2 = calc(s[1]);
						if (invalid) goto __ERROR;
						if (_error && !(_error = false)) goto BUCLE;

						trobat = true;
						conjunt j = conjunts[i].second;
						
						if (chr == '+') j[val1] += val2;
						else if (chr == '-') j[val1] -= val2;
						else if (chr == '*') j[val1] *= val2;
						else if (chr == '/') j[val1] /= val2;

						conjunts.set(i, res[1], j);

						color(COL_RESULTAT);
						cout << s[0] << " = " << conjunts[i].second.toString() << "\n\n";
						color(COL_RESET);
						break;
					}
				}
			}

			for (int i = 0; i < conjunts.compte; i++) {
				if (s[0] == conjunts[i].first) {
					double val = calc(s[1]);
					if (invalid) goto __ERROR;
					if (_error && !(_error = false)) goto BUCLE;
					
					conjunt j = conjunts[i].second;

					if (chr == '+') j += val;
					else if (chr == '-') j -= val;
					else if (chr == '*') j *= val;
					else if (chr == '/') j /= val;

					conjunts.set(i, s[0], j);
					trobat = true;
					color(COL_RESULTAT);
					cout << s[0] << " = " << conjunts[i].second.toString() << "\n\n";
					color(COL_RESET);
					break;
				}
			}
			if (!trobat) for (int i = 0; i < variables.compte; i++) {
				if (s[0] == variables[i].first) {
					double val = calc(s[1]);
					if (invalid) goto __ERROR;
					if (_error && !(_error = false)) continue;

					double x = variables[i].second;

					if (chr == '+') x += val;
					else if (chr == '-') x -= val;
					else if (chr == '*') x *= val;
					else if (chr == '/') x /= val;

					variables.set(i, s[0], x);
					trobat = true;

					color(COL_RESULTAT);
					cout << s[0] << " = " << variables[i].second << "\n\n";
					color(COL_RESET);
					break;
				}
			}
			if (trobat) {
				str nou("");
				for (int i = 0; i < variables.compte; i++) {
					if (i) nou += "\n";
					nou += variables[i].first + "=" + to_string(variables[i].second);
				}
				for (int i = 0; i < conjunts.compte; i++) {
					nou += "\n" + conjunts[i].first + "=" + conjunts[i].second.toString();
				}

				ofstream _arxiu("constants.txt");
				_arxiu << nou;
				_arxiu.close();
				continue;
			}
			color(COL_ERROR);
			cout << "No s'ha trobat la variable " << s[0] << "\n\n";
			color(COL_RESET);
		}
		else if (troba(op, "==") || troba(op, ">") || troba(op, "<")) {
			// Operadors de comparació
			string chr("==");

			if (troba(op, ">=")) chr = ">=";
			else if (troba(op, ">")) chr = ">";
			else if (troba(op, "<=")) chr = "<=";
			else if (troba(op, "<")) chr = "<";

			str_arr membres = explode(op, chr);
			double val1 = calc(membres[0]), val2 = calc(membres[1]);
			if (invalid) goto __ERROR;
			if (_error && !(_error = false)) continue;

			if (chr == "==") {
				if (val1 != val2) goto BOOL_NO;
			}
			else if (chr == ">") {
				if (val1 <= val2) goto BOOL_NO;
			}
			else if (chr == "<") {
				if (val1 >= val2) goto BOOL_NO;
			}
			else if (chr == ">=") {
				if (val1 < val2) goto BOOL_NO;
			}
			else if (chr == "<=") {
				if (val1 > val2) goto BOOL_NO;
			}

			color(COL_RESULTAT);
			cout << "VERTADER (" << val1 << " " << chr << " " << val2 << ")\n\n";
			color(COL_RESET);
			continue;

		BOOL_NO:
			color(COL_RESULTAT);
			cout << "FALS !(" << val1 << " " << chr << " " << val2 << ")\n\n";
			color(COL_RESET);
		}
		else if (troba(op, "=")) {
			while (troba(op, " =")) str_replace(op, " =", "=");
			while (començaAmb(op, " ")) op = substring(op, 1, op.length() - 1);
			auto s = explode(op, '=');

			bool errors = false;

			regex rx("^(\\s*[a-zA-Z][a-zA-Z0-9]*)\\s*(\\(\\s*x\\s*\\))\\s*$");
			if (regex_match(s[0], rx)) {
				if (strpos(s[1], '{') >= 0) goto __ERROR;

				strtrim(s[0], ' ');
				strtrim(s[1], ' ');

				str NOM = s[0];
				strtrim(NOM, "(x)");
				for (int i = 0; i < funcio.compte; i++) {
					if (funcio[i].first == NOM) {
						_error = true;
						break;
					}
				}
				if (_error) {
					color(COL_ERROR);
					cout << "La funcio " << s[0] << " no es pot canviar\n\n";
					color(COL_RESET);
					continue;
				}
				str linia, nou("");
				bool inserir = true, primera = true;

				ifstream arxiu("constants.txt");
				while (getline(arxiu, linia)) {
					str_arr components = explode(linia, '=');

					if (!primera) nou += "\n";
					else primera = false;

					if (inserir && components[0] == s[0] && !(inserir = false)) nou += s[0] + "=" + s[1];
					else nou += linia;
				}
				if (inserir) {
					if (!primera) nou += "\n";
					nou += s[0] + "=" + s[1];
				}
				arxiu.close();

				color(COL_RESULTAT);
				cout << s[0] << " = " << s[1] << "\n\n";
				color(COL_RESET);

				ofstream _arxiu("constants.txt");
				_arxiu << nou;
				_arxiu.close();
				continue;
			}

			int pos = strpos(s[0], '[');
			if (pos > 0) {
				str n("");
				for (int i = pos + 1; i < s[0].length(); i++) {
					if (s[0][i] == ']') break;
					n += s[0][i];
				}
				double x = calc(n);
				if (invalid) goto __ERROR;
				if (_error && !(_error = false)) continue;

				int x1 = (int)x;
				if (x != (double)x1) {
					color(COL_ALERTA);
					cout << "L'index ha de ser sencer.\n\n";
					color(COL_RESET);
					continue;
				}
				if (x1 <= 0) {
					color(COL_ALERTA);
					cout << "L'index ha de ser major a 0.\n\n";
					color(COL_RESET);
					continue;
				}
				str_replace(s[0], "[" + n + "]", "[" + to_string(x1) + "]");			
			}

			color(COL_ERROR);
			for (auto cons : constants) {
				if (cons.first == s[0]) {
					cout << "No es pot canviar el valor d'una constant (" << cons.first << " = " << cons.second << ").\n\n";
					errors = true;
					break;
				}
			}
			if (!errors && troba(s[0], "[]") && (errors = true)) cout << "Invalid per \"[]\".\n\n";
			if (!errors && isdigit(s[0][0]) && (errors = true)) cout << "Les variables no poden comencar amb un digit.\n\n";
			if (!errors && troba(s[0], " ") && (errors = true)) cout << "Les variables no poden tenir espais.\n\n";
			if (!errors) {
				regex rx("^([a-zA-Z]+)\\[([^\\]])\\]$");
				smatch res;
				str x = s[0];
				if (regex_search(s[0], res, rx)) x = res[1];
				for (auto c : x) {
					if (!isdigit(c) && !isalpha(c) && c != '[' && c != ']') {
						cout << "Les variables nomes poden tenir caracters alfanumerics.\n\n";
						errors = true;
						break;
					}
				}
			}
			rx = "^x[0-9]*$";
			if (!errors && regex_match(s[0], rx) && (errors = true)) cout << "Les variables x, x1, x2,... estan reservades per a les funcions.\n\n";
			color(COL_RESET);	
			if (!errors) {
				str nou("");
				strtrim(s[1], ' ');
				if (s[1][0] != '{') {
					double val = calc(s[1]);
					if (invalid) goto __ERROR;
					if (_error && !(_error = false)) continue;

					str linia;
					bool inserir = true, primera = true;

					regex rx("^[a-zA-Z]+[0-9]*[a-zA-Z]*$"), rx1("^[a-zA-Z]+[0-9]*[a-zA-Z]*\\[\\d+\\]$");

					if (regex_match(s[0], rx)) {
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
					}
					else if (regex_match(s[0], rx1)) {
						strtrim(s[0], ']');
						str_arr vec = explode(s[0], '[');
						bool fet = false;
						for (int i = 0; i < conjunts.compte; i++) {
							if (conjunts[i].first == vec[0]) {
								int ind = (int)stod(vec[1]);
								if (ind == 0 || ind > conjunts[i].second.sz()) {
									color(COL_ALERTA);
									cout << "Index fora d'interval.\n\n";
									color(COL_RESET);
									_error = true;
									break;
								}
								// Canviar l'elements
								conjunt j = conjunts[i].second;
								j[ind] = val;
								conjunts.set(i, conjunts[i].first, j);

								for (int j = 0; j < variables.compte; j++) {
									if (j) nou += "\n";
									nou += variables[j].first + "=" + to_string(variables[j].second);
								}
								for (int j = 0; j < conjunts.compte; j++) {
									nou += "\n" + conjunts[j].first + "=" + conjunts[j].second.toString();
								}
								s[0] += "]";
								fet = true;
								break;
							}
						}
						if (_error) {
							_error = false;
							continue;
						}
						if (!fet) {
							color(COL_ERROR);
							cout << "No s'ha trobat el conjunt \"" << vec[0] << "\".\n\n";
							color(COL_RESET);
							continue;
						}
					}
					else goto __ERROR;

					color(COL_RESULTAT);
					cout << s[0] << " = " << redondeig(val, decimals) << "\n\n";
					color(COL_RESET);
				}
				else {
					// Per als conjunts
					conjunt c = conjunt(s[1]);

					str linia;
					bool inserir = true, primera = true;

					ifstream arxiu("constants.txt");
					while (getline(arxiu, linia)) {
						str_arr components = explode(linia, '=');

						if (!primera) nou += "\n";
						else primera = false;

						if (inserir && components[0] == s[0] && !(inserir = false)) nou += components[0] + "=" + c.toString();
						else nou += linia;
					}
					if (inserir) {
						if (!primera) nou += "\n";
						nou += s[0] + "=" + c.toString();
					}
					arxiu.close();

					color(COL_RESULTAT);
					cout << s[0] << " = " << c.toString() << "\n\n";
					color(COL_RESET);
				}

				ofstream _arxiu("constants.txt");
				_arxiu << nou;
				_arxiu.close();
			}
		}
		else {
			// En qualsevol altre cas, operam sens més
			double val = calc(op);
			if (invalid) goto __ERROR;
			if (_error && !(_error = false)) continue;

			// Desar a l'historial
			arxiu = ifstream("historial.txt");
			str linia;
			str_arr vec;

			vec.push_back(to_string(val));
			while (getline(arxiu, linia) && vec.size() < 10) vec.push_back(linia);
			arxiu.close();

			ofstream _arxiu("historial.txt");
			_arxiu << implode(vec, '\n');
			_arxiu.close();

			color(COL_RESULTAT);
			cout << "= " << redondeig(val, decimals) << "\n\n";
			color(COL_RESET);
		}
	}
	return 0;
}
