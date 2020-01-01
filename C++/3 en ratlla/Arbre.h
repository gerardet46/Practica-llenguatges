#include <vector>

class Node {
public:
    J tauler[9];
    int punts;
    int seleccionat;
    std::vector<Node*> proxims;

    Node(J[]);
    ~Node() {};
};

Node::Node(J t[]) { // suposam len(t) = 9
    for (int i = 0; i < 9; i++) {
        this->tauler[i] = t[i];
    }
}

class Arbre {
public:
    std::vector<Node*> nodes;

    Arbre() {};
    ~Arbre() {};
};