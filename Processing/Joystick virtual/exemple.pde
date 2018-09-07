float[] c = {0, 0}; // centre-x, centre-y
float[] pos = {0, 0}; // posició del mòbil per comprovar que les velocitats donades pel joystick quadren

Joystick j; // El joystick

/*
USAR UN CODI PER L'ESTIL PER REESCRIURE EL MÈTODE DE RENDER (CANVI DE COLOR, "ellipseMode", etc)
O BÉ PER INSERIR UN CODI ABANS O DESPRÉS D'ACTUALITZAR LES POSICIONS (NO OBLIDAR POSAR "super.actualitzar();");

class Joys extends Joystick {
  Joys(float _x, float _y, float w, float w_petit, float _extra) {
      super(_x, _y, w, w_petit, _extra);
   }
  
  @Override void render() {
    stroke(200);
    strokeWeight(1);
    ellipseMode(CENTER);
    
    fill(180, 200); // Color del cercle gran (limita al petit)
    ellipse(x, y, ample, ample);
    fill(200, 30, 50); // Color del cercle petit (controlador)
    ellipse(petit[0], petit[1], petit[2], petit[2]);
  }
}
*/

void setup() {
  //size(1024, 720);
  fullScreen();
  
  // Inciam les variables
  c[0] = pos[0] = width / 2;
  c[1] = pos[1] = height / 2;

  j = new Joystick(150, height - 150, 150, 70, 2); // Ajustam el tamany del joystick
  //j.quadricula = false; // No mostrar els punts cardinals al joystick
}
void draw() {
  background(255);
  
  // Dibuixam la graella
  graella(c[0], c[1]);
  
  // Mostram les dades
  fill(0);
  textSize(32);
  if (j.actiu) { // Si estam movent el Joystick
    text("Pendent (y=mx) = " + j.pendent, 10, 60);
    text("Angle d'inclinació: " + degrees(j.angle) + "º", 10, 120);
  } else {
    text("Pendent (y=mx) = 0", 10, 60);
    text("Angle d'inclinació: 0º", 10, 120);
  }
  text("vx = " + j.v.x, 10, 180);
  text("vy = " + j.v.y, 10, 240);
  text("|v| = " + j.v.mag(), 10, 300); // Mòdul del vector velocitat
  
  // Dibuixam la pendent (determinada per la posició del joystick)
  stroke(160, 50, 50);
  strokeWeight(3);
  line(0, c[0] * j.pendent + c[1], width, c[0] * -j.pendent + c[1]);
  
  // El mòbil (un rectangle que se mourà segons la posició del joystick)
  fill(200, 50, 50);
  stroke(0);
  strokeWeight(2);
  rect(pos[0] - 25, pos[1] - 25, 50, 50);
  
  // Dibuixam una línia paralel·la a la pendent per mostrar el camí exacte que seguirà el mòbil
  stroke(100, 70, 160);
  strokeWeight(3);
  line(0, pos[0] * j.pendent + pos[1], width, (width - pos[0]) * -j.pendent + pos[1]);
  
  // Actualitzam el "joystick"
  j.actualitzar();
  j.render(); // El mostram
  
  if (j.actiu) {
    // Si l'estam presionant, que es mogui on cal (multiplicam per 2 per a que se vegi millor)
    pos[0] += j.v.x;
    pos[1] += j.v.y;
  }
  if (pos[0] < 0 || pos[0] > width || pos[1] < 0 || pos[1] > height) { // Si el mòbil no es veu (surt de la pantalla)
    pos[0] = c[0];
    pos[1] = c[1];
  }
}

void graella(float x, float y) {
  int inc = 0;
  
  // Eixos cartesians al (x, y) (origen)
  strokeWeight(2);
  stroke(50);
  line(x, 0, x, height);
  line(0, y, width, y);
  
  strokeWeight(1);
  stroke(210);
  // Línies verticals
  while ((inc += 50) < width) line(x + inc, 0, x + inc, height);
  inc = 0;
  while ((inc -= 50) > -x) line(x + inc, 0, x + inc, height);
  
  // Línies horitzontals
  inc = 0;
  while ((inc += 50) < height) line(0, y + inc, width, y + inc);
  inc = 0;
  while ((inc -= 50) > -x) line(0, y + inc, width, y + inc);
}
