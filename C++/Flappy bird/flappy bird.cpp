#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;
using namespace sf;

#define ALT_TERRA 150

#include "Aucell.h"
#include "Tub.h"
#include "Terra.h"

Aucell oc(120, 150);
Tub tubs[10];
Terra terra;

bool pausa = false;

int main() {
	srand(time(NULL));

	RenderWindow joc(VideoMode(1080, 720), "Flappy bird", Style::Fullscreen/*, Style::Titlebar | Style::Close*/);

	joc.setView(View(FloatRect(0, 0, joc.getSize().x, joc.getSize().y)));

	// Font
	Font font;
	font.loadFromFile("fonts\\AgencyFB.ttf");

	// Imatges
	Texture img_aucell, img_terra, img_tub;
	img_aucell.loadFromFile("images/aucell.png");
	img_terra.loadFromFile("images/terra.png");
	img_tub.loadFromFile("images/tub.png");

	oc.img(&img_aucell);
	terra.img(&img_terra);

	tubs[0] = Tub(&joc, &img_tub);
	
	float dist_anterior = joc.getSize().x, f_antic = 0;
	int punts = 0;

	// Bucle del joc
	while (joc.isOpen()) {
		Event e;
		while (joc.pollEvent(e)) {
			if (e.type == Event::Closed) joc.close();

			if (e.type == Event::KeyPressed) {
				if (e.key.code == Keyboard::Space || e.key.code == Keyboard::Up) {
					if (pausa) pausa = oc.terra = false;
					else oc.botar();
				}
				if (e.key.code == Keyboard::Enter && oc.terra) {
					if (pausa) pausa = oc.terra = false;
					else {
						for (auto& t : tubs) t = Tub();
						oc.vel = 0;
						oc.y = 150;
						oc.angle = 0;
						oc.caure = oc.terra = false;
						punts = 0;
					}
				}
				if (e.key.code == Keyboard::P) {
					pausa = !pausa;
					oc.terra = pausa;
				}
			}

			if (e.type == Event::Resized)
			{
				FloatRect visibleArea(0, 0, e.size.width, e.size.height);
				//joc.setView(View(visibleArea));

				for (auto& t : tubs) {
					if (t.inici) break;

					t.troç[2] = ceil((joc.getSize().y - 100) / 10.0f) - t.troç[0] - t.troç[1];
				}
			}
		}
		auto f = 70 - 70 * cos(3.14159265 * punts / 100); // brillantor (cada 100 es fa de vespre)
		if (f != f_antic) {
			oc.im.setColor(Color(255 - f, 255 - f, 255 - f));
			terra.im.setColor(Color(255 - f, 255 - f, 255 - f));
			for (auto& t : tubs) {
				t.cos.setColor(Color(255 - f, 255 - f, 255 - f));
				t.extrem.setColor(Color(255 - f, 255 - f, 255 - f));
			}
		}

		if (!oc.terra) {
			// Quan un desapareix, movem tots al principi de l'array
			if (tubs[0].final) {
				for (int i = 0; i < 9; i++) {
					tubs[i] = tubs[i + 1];
				}
			}
			// Calculam la distància del darrer tub per a posar-ne un altre
			if ((dist_anterior -= tubs[0].vel) < joc.getSize().x - 550) {
				dist_anterior = joc.getSize().x;
				for (auto& t : tubs) {
					if (t.inici) {
						t = Tub(&joc, &img_tub, f);
						break;
					}
				}
			}

			// Comprovam col·lisions
			if (terra.xoca(oc, &joc)) {
				// GAME OVER, si oc.caure = false
			}
		}
		f_antic = f;

		// Dibuixam tot
		joc.clear(Color(180 - f, 220 - f, 255 - f));

		// Tubs
		for (auto& t : tubs) {
			if (t.inici) break;
			if (!oc.terra && !oc.caure) t.actualitzar();
			t.render(&joc);

			if (abs(t.x - oc.x) < t.ample * 1.5 && t.xoca(oc, &joc)) {
				// GAME OVER
			}
			float val = oc.x - t.x - t.ample;
			if (val > 0 && val < t.vel * 2) punts++;
		}

		// Terra
		if (!oc.terra && !oc.caure) terra.actualitzar();
		terra.render(&joc);
		
		RectangleShape s(Vector2f(joc.getSize().x, ALT_TERRA - 22));
		s.setPosition(0, joc.getSize().y - ALT_TERRA + 33);
		s.setFillColor(Color(f));
		joc.draw(s);

		// Aucell
		if (!oc.terra) oc.actualitzar();
		oc.render(&joc);

		// Texts i demés
		Text t(to_string(punts), font, 120);
		t.setStyle(Text::Bold);
		t.setPosition(joc.getSize().x / 2, 20);
		t.setFillColor(Color::Black);
		joc.draw(t);
		t.setCharacterSize(110);
		t.setFillColor(Color::White);
		t.move(1, 7);
		joc.draw(t);

		joc.display();
	}

	return 0;
}