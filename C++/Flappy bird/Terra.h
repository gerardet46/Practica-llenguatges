#pragma once

class Terra {
public:
	float x = 0, vel = 0.5, ample = 72 * 1.5;
	Sprite im;

	void actualitzar();
	void render(RenderWindow* r);
	void img(Texture* t);
	bool xoca(Aucell& a, RenderWindow* r);

	Terra();
};
Terra::Terra(){}

inline void Terra::img(Texture* t) {
	im = Sprite(*t);
	im.setScale(1.5, 1.5);
}

inline void Terra::actualitzar() {
	x -= vel;
	if (x <= -ample) x = 0;
}

inline void Terra::render(RenderWindow* r) {
	RectangleShape rect(Vector2f(r->getSize().x, ALT_TERRA));
	rect.setPosition(0, r->getSize().y - ALT_TERRA);
	rect.setFillColor(Color(232, 206, 153));

	r->draw(rect);

	im.setPosition(x, r->getSize().y - ALT_TERRA);
	int i = x, w = r->getSize().x;
	while (i < w) {		
		r->draw(im);
		im.move(ample, 0);
		i += ample;
	}
}
inline bool Terra::xoca(Aucell& a, RenderWindow* r) {
	if (r->getSize().y - a.y - 20 < ALT_TERRA) {
		a.terra = true;
		return true;
	}
	return false;
}