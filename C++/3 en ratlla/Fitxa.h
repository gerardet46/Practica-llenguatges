#include "vars.h"
#include "Arbre.h"
#include "Cervell.h"

/*
enum J {};
class Cervell {};
*/
class Fitxa {
public:
    J jugador;
    Cervell cervell;

    Fitxa(J, Cervell);
    ~Fitxa();
};

Fitxa::Fitxa(J _jugador, Cervell c) {
    jugador = _jugador;
    cervell = c;
    cervell.fitxa = _jugador;
}

Fitxa::~Fitxa() {}
