/*
Presionau 1 per jugar en primer torn envers l'IA, 2 per a què l'IA jugui primer i 3 per jugar entre dues persones físiques.
ARXIUS:
main.cpp -> arxiu principal del programa
vars.h -> conté les definicións de fitxes, tauler i el mètode de verificació del tauler
arbre.h -> simple classe per crear un arbre amb nodes (per a l'IA)
cervell.h -> l'algoritme d'intel·ligència artificial
Fitxa.h -> definició de la classe per a un jugador (té un cervell i una fitxa assignada)
*/

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <iostream>

using namespace sf;
#define W 800
#define BARRA 30

//#include "vars.h"
//#include "Cervell.h"
#include "Fitxa.h"

void dibuixar_tauler(RenderWindow* joc) {
    RectangleShape rect = RectangleShape(Vector2f(W, 4));
    rect.setFillColor(Color(160, 160, 160));
    
    rect.setPosition(0, W / 3 - 2);
    joc->draw(rect);

    rect.move(0, W / 3);
    joc->draw(rect);

    rect.setOrigin(W / 2, 2);
    rect.setRotation(90);
    rect.setPosition(W / 3, W / 2);
    joc->draw(rect);

    rect.move(W / 3, 0);
    joc->draw(rect);
}

bool dibuixant = false;
int POSICIO = 0;
float opacitat = 0;

void renderX(Vector2f pos, RenderWindow* joc, int _pos) {
    RectangleShape rect = RectangleShape(Vector2f(W / 8, W / 8));
    rect.setFillColor(Color(0, 148, 84));
    
    rect.setOutlineColor(Color(30, 30, 30));
    rect.setOutlineThickness(2);

    if (dibuixant && _pos == POSICIO && tauler[POSICIO] == J::X) {
        opacitat += 1;
        if (opacitat >= 255) {
            opacitat = 255;
            dibuixant = false;
            opacitat = 0;
        }
        else rect.setFillColor(Color(0, 148, 84, opacitat));
    }
    
    rect.setPosition(pos + Vector2f(5 * W / 48, 5 * W / 48)); // centram sa imatge
    joc->draw(rect);
}

void renderO(Vector2f pos, RenderWindow* joc, int _pos) {
    CircleShape rect = CircleShape(W / 12);
    rect.setFillColor(Color(181, 136, 0));
    
    rect.setOutlineColor(Color(30, 30, 30));
    rect.setOutlineThickness(2);

    if (dibuixant && _pos == POSICIO && tauler[POSICIO] == J::O) {
        opacitat += 1;
        if (opacitat >= 255) {
            opacitat = 255;
            dibuixant = false;
            opacitat = 0;
        }
        else rect.setFillColor(Color(181, 136, 0, opacitat));
    }
    
    rect.setPosition(pos + Vector2f(W / 12, W / 12)); // centram sa imatge
    joc->draw(rect);
}

int main(int argc, const char** argv) {
    RenderWindow* joc = new RenderWindow(VideoMode(W, W), "3 en ratlla!", Style::Titlebar | Style::Close);

    auto* J1 = new Fitxa(J::X, new JFisic());
    auto* J2 = new Fitxa(J::O, new IA());
    J2->cervell.demanar = false; // en teoria s'haria de posar al iniciar new IA()
    J2->cervell.IA = true;

    int torn = 0;
    bool esperar = false;
    bool acabat = false;
    
    while (joc->isOpen()) {
        Event e;
        while (joc->pollEvent(e)) {
            if (e.type == Event::Closed) joc->close();
            if (esperar && e.type == Event::MouseButtonPressed) {
                auto pos = sf::Mouse::getPosition() - joc->getPosition();
                pos.y -= BARRA;
                pos = pos * 3 / W;
                
                //std::cout << pos.x << ", " << pos.y << std::endl;
                int index = 3 * pos.y + pos.x;

                if (!dibuixant) {
                    if (torn == 1) {
                        if (tauler[index] == J::N) {
                            tauler[index] = J1->jugador;
                            esperar = false;
                            torn = 2;
                        }
                    } else {
                        if (tauler[index] == J::N) {
                            tauler[index] = J2->jugador;
                            esperar = false;
                            torn = 1;
                        }
                    }
                }
            }
            if (e.type == Event::KeyPressed) {
                if (e.key.code == Keyboard::Space) {
                    acabat = false;
                    torn = 0;
                    for (int i = 0; i < 9; i++) tauler[i] = J::N;
                } else if (e.key.code == Keyboard::Num1) {
                    J1 = new Fitxa(J::X, new JFisic());
                    J2 = new Fitxa(J::O, new IA());
                    J2->cervell.demanar = false; // en teoria s'haria de posar al iniciar new IA()
                    J2->cervell.IA = true;

                    acabat = false;
                    torn = 0;
                    for (int i = 0; i < 9; i++) tauler[i] = J::N;
                } else if (e.key.code == Keyboard::Num2) {
                    J2 = new Fitxa(J::X, new JFisic());
                    J1 = new Fitxa(J::O, new IA());
                    J1->cervell.demanar = false; // en teoria s'haria de posar al iniciar new IA()
                    J1->cervell.IA = true;

                    acabat = false;
                    torn = 0;
                    for (int i = 0; i < 9; i++) tauler[i] = J::N;
                } else if (e.key.code == Keyboard::Num3) {
                    J1 = new Fitxa(J::X, new JFisic());
                    J2 = new Fitxa(J::O, new JFisic());

                    acabat = false;
                    torn = 0;
                    for (int i = 0; i < 9; i++) tauler[i] = J::N;
                }
            }
        }

        // verificam es tauler
        auto r = verificar(tauler);
        if (r != J::N) {
            if (!acabat) {
                if (r == J::E) std::cout << "EMPAT!" << std::endl;
                else if (r == J::X) std::cout << "Guanya 1!" << std::endl;
                else if (r == J::O) std::cout << "Guanya 2!" << std::endl;
                acabat = true;
            }
            goto DIBUIXAR;
        }
        if (dibuixant) goto DIBUIXAR;
        if (torn == 1) {
            //std::cout << J1->cervell.demanar << std::endl;
            if (J1->cervell.demanar) esperar = true;
            else {
                POSICIO = ((IA)(J1->cervell)).seguent();
                tauler[POSICIO] = J1->jugador;
                torn = 2;
                dibuixant = true;
            }
        } else if (torn == 2) {
            if (J2->cervell.demanar) esperar = true;
            else {
                //J2->cervell.seguent();
                POSICIO = ((IA)(J2->cervell)).seguent();
                tauler[POSICIO] = J2->jugador;
                dibuixant = true;
                torn = 1;
            }
        }

    DIBUIXAR:
        joc->clear(Color(66, 66, 66));

        // dibuixam es tauler
        dibuixar_tauler(joc);

        // dibuixam ses fitxes
        for (int i = 0; i < 9; i++) {
            auto x = tauler[i];
            Vector2f pos = Vector2f((i % 3) * W / 3, i / 3 * W / 3);
            if (x == J::X) {
                renderX(pos, joc, i);
            } else if (x == J::O) {
                renderO(pos, joc, i);
            }
        }

        joc->display();

        if (torn == 0) torn++;
    }
    return 0;
}
