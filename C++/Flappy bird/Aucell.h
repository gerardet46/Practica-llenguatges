#pragma once

class Aucell {
public:
	float acc = 0.01, x = 25, y = 0, vel = 0, max_vel = 2, bot = 1.5, angle = 0;
	bool terra = false, caure = false;
	Sprite im;

	void botar();
	void actualitzar();
	void render(RenderWindow* r);
	void img(Texture* img);

	Aucell(float _x, float _y);
};

Aucell::Aucell(float _x, float _y) {
	x = _x;
	y = _y;	
}

inline void Aucell::img(Texture* img) {
	im = Sprite(*img);
	im.setOrigin(150, 150); // La imatge és de 300x300
	im.setScale(Vector2f(0.27, 0.27));
}

inline void Aucell::botar() {
	if (!caure) vel = -bot;
}

inline void Aucell::actualitzar() {
	if (vel + acc < max_vel) vel += acc;
	y += vel;
}

inline void Aucell::render(RenderWindow* r) {
	if (!terra) {
		im.setPosition(x, y);

		if (vel < 0 && angle > -20)
			im.setRotation(angle -= 1);
		else if (vel > 0.3 && angle < 90)
			im.setRotation(angle += 0.3);
	}

	r->draw(im);
}