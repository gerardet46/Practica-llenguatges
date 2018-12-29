/*
Aquest arxiu completa les funcions per a string seguint una mica el model de PHP. Escurça el codi i facilita la comprensió.
En totes les funcions, el primer argument és l'string amb la què harem de comprovar (la "x" de la funció).
A vegades la trobarem amb el signe "&", que vol dir que no torna res però es modifica la variable passada (referència).
*/

#pragma once

#include <vector>
#include <string>

#define USA_STR using namespace gstring
#define str string
#define str_arr vector<string>

using namespace std;

namespace gstring {
	str to_string(char c) {
		str r("");
		r += c;
		return r;
	}

	void strtrim(str &in, str c) {
		str r = "";
		for (auto ch : in) {
			bool posar = true;
			for (auto chs : c) {
				if (ch == chs) {
					posar = false;
					break;
				}
			}
			if (posar) r += ch;
		}
		in = r;
	}
	void strtrim(str &in, char* c) {
		str chars(c);
		strtrim(in, chars);
	}
	void strtrim(str &in, char c) {
		str chars = to_string(c);
		strtrim(in, chars);
	}

	void str_replace(str &in, char c1, char c2) {
		for (int i = 0; i < in.length(); i++) {
			if (in[i] == c1) in[i] = c2;
		}
	}
	void str_replace(str &in, char c1, str rep) {
		str r = "";
		for (int i = 0; i < in.length(); i++) {
			if (in[i] == c1) r += rep;
			else r += in[i];
		}
		in = r;
	}
	void str_replace(str &in, str s1, str s2) {
		size_t pos = in.find(s1);

		while (pos != string::npos) {
			in.replace(pos, s1.size(), s2);
			pos = in.find(s1, pos + s2.size());
		}
	}
	str_arr explode(str in, str chars, bool deixar = false) {
		str_arr r = str_arr();
		str temp("");
		for (auto c : in) {
			bool posar = true;
			for (auto c1 : chars) {
				if (c == c1) {
					if (temp.length()) r.push_back(temp);
					temp = deixar ? to_string(c) : "";
					posar = false;
					break;
				}
			}
			if (posar) temp += c;
		}
		if (temp.length()) r.push_back(temp);
		if (!r.size()) r.push_back(in);
		return r;
	}

	str_arr explode(str in, char c, bool deixar = false) {
		auto a = to_string(c);
		return explode(in, a, deixar);
	}

	str implode(str_arr in, str chars) {
		string r("");
		for (int i = 0; i < in.size(); i++) {
			if (i) r += chars;
			r += in[i];
		}
		return r;
	}
	str implode(str_arr in, char c) {
		auto a = to_string(c);
		return implode(in, a);
	}

	int strpos(str in, str cerca);
	bool troba(str in, str cerca) {	return strpos(in, cerca) >= 0;}
	int strpos(str in, str cerca) {
		size_t r = in.find(cerca);
		return r == string::npos ? -1 : r;
	}
	int strpos(str in, char c) {
		int pos = 0;
		for (auto ch : in) {
			if (++pos && c == ch) return pos - 1;
		}
		return - 1;
	}
	
	str substring(str in, int index, int length) {
		str r("");
		while (r.length() < length) {
			r += in[index];
			index++;
		}
		return r;
	}

	void strtolower(str &in) {
		for (int i = 0; i < in.length(); i++)
			in[i] = tolower(in[i]);
	}
	void strtoupper(str &in) {
		for (int i = 0; i < in.length(); i++)
			in[i] = toupper(in[i]);
	}

	bool començaAmb(str in, str cerca) {
		if (cerca.length() > in.length()) return false;
		for (int i = 0; i < cerca.length(); i++) {
			if (in[i] != cerca[i]) return false;
		}
		return true;
	}
	bool acabaAmb(str in, str cerca) {
		if (cerca.length() > in.length()) return false;
		for (int i = 0; i < cerca.length(); i++) {
			if (in[in.length() - i - 1] != cerca[cerca.length() - i - 1]) return false;
		}
		return true;
	}
}
