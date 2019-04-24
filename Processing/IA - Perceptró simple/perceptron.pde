Punt[] punts = new Punt[10000];
Perceptron cervell;

float m = random(0.5, 4);
float n = random(-0.5, 0.5);
float f(float x) {
  return m * x + n;
}

void init() {
  cervell = new Perceptron(3);
  for (int i = 0; i < punts.length; i++) {
    punts[i] = new Punt();
  }
  m = random(0.5, 4);
  n = random(-0.5, 0.5);
  totbe = false;
}
void entrenar() {
  for (Punt p : punts) {
    float[] coord = {p.x, p.y, p.b};
    cervell.entrenar(coord, p.t);
  }
}

void setup() {
  size(1400, 900);
  init();
  //frameRate(20);
}

boolean totbe = true;
void draw() {
  background(255);
  
  totbe = true;
  for (Punt p : punts) {
    p.render();
    
    float[] coord = {p.x, p.y, p.b};
    int r = cervell.comprova(coord);
    
    if (r != p.t) {
      fill(200, 80, 80);
      ellipse(pixelX(p.x), pixelY(p.y), 12, 12);
      fill(200, 80, 80, 100);
      ellipse(pixelX(p.x), pixelY(p.y), 48, 48);
      totbe = false;
    }
  }

  strokeWeight(6);
  stroke(180, 180, 0);

  float[] a = {-1, f(-1), 1, f(1)}; 
  //line(pixelX(a[0]), pixelY(a[1]), pixelX(a[2]), pixelY(a[3]));

  strokeWeight(4);
  stroke(20);
  cervell.linia();
  if (!totbe) entrenar();
  
  strokeWeight(1);
  if (totbe) {
    fill(255, 100);
    rect(0, 0, width, height);
    fill(20);
    textSize(108);
    textAlign(CENTER);
    text(String.format("y=%fx%s%f", -cervell.pes[0] / cervell.pes[1], cervell.pes[2] / cervell.pes[1] < 0 ? "+" : "", -cervell.pes[2] / cervell.pes[1]), width / 2, height / 2 - 48 / 2);
  }
}
void mousePressed() {
  init();
}
