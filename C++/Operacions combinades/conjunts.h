#pragma once

#include "gstring.h"
#include <utility>

USA_STR;

bool invalid = false, _error = false;
double calc(string op);

using namespace std;

// Diccionari (dues llistes)
template<typename T1, typename T2>
class dicc {
public:
	vector<T1> nom;
	vector<T2> valor;
	int compte;

	void reset() {
		nom = vector<T1>();
		valor = vector<T2>();
		compte = 0;
	}

	void afegir(T1 n, T2 v) {
		nom.push_back(n);
		valor.push_back(v);
		compte++;
	}
	void afegir(pair<T1, T2> n) {
		nom.push_back(n.first);
		valor.push_back(n.second);
		compte++;
	}
	void afegir(pair<T1, T2> *n, int sz) {
		for (int i = 0; i < sz; i++) {
			auto x = n[i];
			afegir(x);
		}
	}
	void afegir(dicc<T1, T2> n) {
		for (int i = 0; i < n.compte; i++) {
			auto x = n[i];
			afegir(x);
		}
	}
	void esborrar(T1 n) {
		vector<T1> r1;
		vector<T2> r2;
		int i = 0;
		for (auto x : nom) {
			if (x != n) {
				r1.push_back(x);
				r2.push_back(valor[i]);
			}
			i++;
		}
		nom = r1;
		valor = r2;
		compte = r1.size();
	}
	void set(int x, T1 val1, T2 val2) {
		nom[x] = val1;
		valor[x] = val2;
	}
	void set(int x, pair<T1, T2> val) {
		nom[x] = val.first;
		valor[x] = val.second;
	}
	int cerca(T1 x) {
		for (int i = 0; i < compte; i++) {
			if (nom[i] == x) return i;
		}
		return -1;
	}

	pair<T1, T2> operator[](int x) {
		auto val = make_pair(nom[x], valor[x]);
		return val;
	}
	void operator=(const dicc<T1, T2>& d) {
		this->nom = d.nom;
		this->valor = d.valor;
		this->compte = d.compte;
	}
	dicc<T1, T2> operator+(const dicc<T1, T2>& a) const {
		dicc<T1, T2> r = *this;
		dicc<T1, T2> t = a;

		for (int i = 0; i < t.compte; i++) r.afegir(t[i]);
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
// Classe per incorporar conjunts
class conjunt {
private:
	str_arr elements;

	void set_elements() {
		elements = str_arr();
		for (auto x : valors) elements.push_back(to_string(x));
	}
public:	
	vector<double> valors;

	int sz() { return valors.size(); }
	str toString(bool claus = true) {
		str r("");
		if (claus) r += "{";
		set_elements();
		r += implode(elements, ',');
		if (claus) r += "}";
		return r;
	}
	conjunt toConjunt(str c) {
		conjunt t = conjunt();
		strtrim(c, "{} ");
		if (c == "") return t;

		t.elements = explode(c, ',');
		for (auto x : t.elements) {
			t.valors.push_back(calc(x));
			if (invalid) return conjunt();
		}
		return t;
	}

	void afegir(double x) {
		valors.push_back(x);
	}
	void afegir(double x, int pos) {
		vector<double> r;
		for (int i = 0; i < pos; i++) r.push_back(valors[i]);
		r.push_back(x);
		for (int i = pos; i < sz(); i++)  r.push_back(valors[i]);
		valors = r;
	}
	void esborrar(int pos) {
		vector<double> r;
		for (int i = 0; i < sz(); i++) {
			if (i != pos) r.push_back(valors[i]);
		}
		valors = r;
	}
	void esborrar(double val) {
		vector<double> r;
		for (auto x:valors) {
			if (x != val) r.push_back(x);
		}
		valors = r;
	}
	void esborrar_tot() {
		valors = vector<double>();
	}
	void esborrar_tot(conjunt &c) {
		c.valors = vector<double>();
	}
	
	double& operator[](int x) { return valors[x - 1]; }

	void operator=(const conjunt& d) {
		this->valors = d.valors;
	}
	conjunt operator+(double a) {
		conjunt c = *this;
		c.valors.push_back(a);
		return c;
	}
	conjunt& operator+=(double a) {
		conjunt& c = *this;
		c.valors.push_back(a);
		return c;
	}
	conjunt operator-(double a) {
		conjunt c = conjunt();
		for (auto x : this->valors) {
			if (x != a)	c.valors.push_back(x);
		}
		return c;
	}
	conjunt& operator-=(double a) {
		conjunt b = *this;
		conjunt& c = *this;
		esborrar_tot(c);
		for (auto x : b.valors) {
			if (x != a) c.valors.push_back(x);
		}
		return c;
	}
	conjunt operator*(double a) {
		conjunt c = *this;
		for (auto &x : c.valors) x *= a;
		return c;
	}
	conjunt& operator*=(double a) {
		conjunt& c = *this;
		for (auto &x : c.valors) x *= a;
		return c;
	}
	conjunt operator/(double a) {
		conjunt c = *this;
		for (auto &x : c.valors) x /= a;
		return c;
	}
	conjunt& operator/=(double a) {
		conjunt& c = *this;
		for (auto &x : c.valors) x /= a;
		set_elements();
		return c;
	}

	conjunt() {
		valors = vector<double>();
		elements = str_arr();
	}
	conjunt(vector<double> vals) { valors = vals; conjunt(); }
	conjunt(str vals) {
		auto c = toConjunt(vals);
		if (invalid) return;
		this->valors = c.valors;
		this->elements = c.elements;
		conjunt();
	}
};