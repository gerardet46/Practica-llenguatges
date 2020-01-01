//#pragma once

enum J {N = 0, X = 1, O = 2, E = 3}; // sa "E" és per s'empat
J tauler[9] = {N,N,N,N,N,N,N,N,N};
//J tauler[9] = {N,X,N,O,N,X,X,N,O};

J verificar(J t[]) {
    // files i columnes
    for (int i = 0; i < 3; i++) {
        if (t[3 * i] == t[3 * i + 1] && t[3 * i] == t[3 * i + 2] && t[3*i] != J::N) {
            return t[3*i];
        }
        if (t[i] == t[i + 3] && t[i] == t[i + 6] && t[i] != J::N) {
            return t[i];
        }
    }
    // diagonals
    if (t[0] == t[4] && t[4] == t[8] && t[4] != J::N) return t[0];
    if (t[2] == t[4] && t[4] == t[6] && t[4] != J::N) return t[2];
    
    // comprovam si queden buits
    for (int i = 0; i < 9; i++) {
        if (t[i] == J::N) return J::N; // continuam jugant
    }
    // en cas d'empat
    return J::E;
}