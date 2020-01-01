//#pragma once

class Cervell {
public:
    bool demanar;
    J fitxa;
    virtual int seguent() {return 0;};

    bool IA = false;

    Cervell();
    Cervell(bool);
    ~Cervell();
};

Cervell::Cervell() {}
Cervell::Cervell(bool _demanar) {
    demanar = _demanar;
}

Cervell::~Cervell() {}


class JFisic : Cervell {
public:
    // aquest no ha de calcular es mètode de següent()
    int seguent() {return 0;};
    JFisic();
    ~JFisic();
};

JFisic::JFisic() {this->demanar = true;}

class IA : Cervell {
public:
    // aquest si tendrà sa funció per calcular es següent
    int seguent() override;
    Arbre* arbre;

    IA();
    IA(Cervell&);
    ~IA() {};

private:
    std::vector<Node*> generar(J[], bool); // calculam es seguents nodes
};

IA::IA() {this->demanar = false;}
IA::IA(Cervell& c) {
    this->demanar = c.demanar;
    this->fitxa = c.fitxa;
}

std::vector<Node*> IA::generar(J t[], bool contrincant) {
    std::vector<Node*> R;

    J _t[9] = {};
    for (int i = 0; i < 9; i++) {
        _t[i] = t[i];
    }

    if (contrincant) {
        // si es es torn des contrincant
        J fit = (this->fitxa == J::X) ? J::O : J::X;
        for (int i = 0; i < 9; i++) {
            if (_t[i] == J::N) {
                _t[i] = fit;
                Node* nou = new Node(_t);
                nou->seleccionat = i;

                auto r = verificar(_t);
                if (r == J::E) nou->punts = 0;
                else if (r == J::N) nou->punts = 1;
                else if (r == this->fitxa) nou->punts = 2;
                else nou->punts = -1;

                // calculam es próxims en cas que se continuï es joc
                int min = 2;
                if (nou->punts == 1) {
                    nou->proxims = generar(_t, !contrincant);
                    // CALCULAM PUNTUACIÓ FINAL PER AQUEST TAULER
                    for (auto x : nou->proxims) {
                        if (x->punts < min) min = x->punts;
                    }
                    nou->punts = min;
                }

                R.push_back(nou);
                _t[i] = J::N;
            }
        }
        return R;
    }

    for (int i = 0; i < 9; i++) { 
        if (_t[i] == J::N) {
            _t[i] = this->fitxa;
            Node* nou = new Node(_t);
            nou->seleccionat = i;

            auto r = verificar(_t);
            if (r == J::E) nou->punts = 0;
            else if (r == J::N) nou->punts = 1;
            else if (r == this->fitxa) nou->punts = 2;
            else nou->punts = -1;

            // calculam es próxims en cas que se continuï es joc
            int min = 2;
            if (nou->punts == 1) {
                nou->proxims = generar(_t, !contrincant);
                // CALCULAM PUNTUACIÓ FINAL PER AQUEST TAULER
                for (auto x : nou->proxims) {
                    if (x->punts < min) min = x->punts;
                }
                nou->punts = min;
            }

            R.push_back(nou);
            _t[i] = J::N;
        }
    }
    // Domés volem es que tenguin millor puntuació
    int max = -1;
    std::vector<Node*> r2;
    for (auto x : R) {
        if (x->punts > max) max = x->punts;
    }
    for (auto x : R) {
        if (x->punts == max) r2.push_back(x);
    }
    return r2;
}

int IA::seguent() {
    // TODO: ALGORITME PER CERCAR SA MILLOR POSSIBILITAT
    arbre = new Arbre();
    if (arbre->nodes.size() == 0) arbre->nodes = this->generar(tauler, false);
    else {
        // en teoria no hauria de passar això
    }
    int i = 0; // esborrar-ho, és domés per comprovar s'arbre
    // seleccionam sa millor
    int max = -1, posicio = 0;
    for (auto x : arbre->nodes) {
        if (x->punts > max) {
            max = x->punts;
            posicio = x->seleccionat;
        }
    }
    //tauler[posicio] = this->fitxa;
    return posicio;
}