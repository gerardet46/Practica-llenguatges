#pragma once

bool colisio(Rect<float> r1, Rect<float> r2) {
	if (r1.left <= r2.left + r2.width && r1.left + r1.width >= r2.left && r1.top <= r2.top + r2.height && r1.top + r1.height >= r2.top)
		return true;
	return false;
}

class Tub {
public:
	float sep = 200, top = 0, ample = 160, x = 0, vel = 0.5;
	int troç[3] = {}; // [adalt, separacio, abaix]
	bool inici = true, final = false;
	Sprite s, cos, extrem;

	void actualitzar();
	void render(RenderWindow* r);
	bool xoca(Aucell& a, RenderWindow* r);

	Tub();
	Tub(RenderWindow* r, Texture* t, float b);
	~Tub();
};

Tub::Tub() {} // Iniciar per a que no es moguin
Tub::Tub(RenderWindow* r, Texture* t, float b = 0) {
	s = Sprite(*t);
	s.setScale(ample / 564, 1); // 564 * x = ample -> x = ample / 564
	s.setColor(Color(255 - b, 255 - b, 255 - b));
	cos = s;
	extrem = s;
	cos.setTextureRect(IntRect(0, 250, 564, 10)); // Fem troços de 10
	extrem.setTextureRect(IntRect(0, 0, 564, 212));
	extrem.setScale(ample / 564, ample / 564);

	x = r->getSize().x;
	int tot_troços = ceil((r->getSize().y - ALT_TERRA) / 10.0f);

	troç[1] = sep / 10;
	troç[0] = rand() % (tot_troços - troç[1] - 20) + 10;
	troç[2] = tot_troços - troç[0] - troç[1];

	top = troç[0] * 10;
	inici = false;
}
Tub::~Tub() { final = true; }

inline void Tub::actualitzar() {
	if (inici) return;

	x -= vel;
	if (x < -ample) {
		vel = 0;
		final = true;
	}
}

inline void Tub::render(RenderWindow* r) {
	if (inici) return;

	cos.setPosition(x, 0);
	for (int i = 0; i < troç[0] + troç[1] + troç[2]; i++) {
		if (i == troç[0]) i += troç[1];

		cos.setPosition(x, i * 10);
		r->draw(cos);	
	}
	extrem.setPosition(x, top - 212 * ample / 564); // 212 * 0.177 (l'escala)
	r->draw(extrem);
	extrem.setPosition(x, top + sep);
	r->draw(extrem);
}

inline bool Tub::xoca(Aucell& a, RenderWindow* r) {
	auto r1 = Rect<float>(a.x - 20, a.y - 25, 40, 50);
	auto r2 = Rect<float>(x, -10000, ample - 64 * ample / 564, top + 10000);
	auto r3 = Rect<float>(x, top + sep, ample - 64 * ample / 564, r->getSize().y - top - sep);

	if (colisio(r1, r2)) {
		a.caure = true;
		if (a.vel < 0.2) a.vel = 0.2;
		return true;
	}
	if (colisio(r1, r3)) {
		a.caure = true;
		if (a.vel < 0.2) a.vel = 0.2;
		return true;
	}
	
	return false;
}