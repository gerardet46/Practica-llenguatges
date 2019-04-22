boolean array0(int[] dades) {
  for (int i = 0; i < dades.length; i++)
    if (dades[i] != 0) return false;
   return true;
}
boolean arr_conte(int[] dades, int val) {
  for (int i = 0; i < dades.length; i++)
    if (dades[i] == val) return true;
   return false;
}
int[] creararray(int N, int num) {
  int[] r = new int[N];
  for (int i = 0; i < N; i++) r[i] = num;
  return r;
}

// Classe per inserir botons al programa
class Boto {
  float x, y, w, h;
  int sz = 28, defas = 0;
  String text;
  boolean mouse_over = false;
  boolean released = false;
  private boolean _down = false;
  color c;
  PFont f;

  Boto(float _x, float _y, float _w, float _h, String _text, PFont font) {
    x = _x;
    y = _y;
    w = _w;
    h = _h;
    text = _text;
    f = font;
  }

  void actualitzar() {
    if (mouseX - x < w && x <= mouseX && mouseY - defas - y < h && y + defas <= mouseY) {
      if (!mouse_over) {
        mouse_over = true;
        cursor(HAND);
      }
      if (down) _down = true;
      else if (_down) {
        released = true;
        _down = false;
      }
    } else if (mouse_over) {
      mouse_over = false;
      if (_down) released = true;
      cursor(ARROW);
    }
  }

  void render() {
    stroke(c);
    strokeWeight(2);
    fill(255, 0);
    if (mouse_over) fill(255, 50);
    if (down && mouse_over) fill(255, 100);

    rect(x, y, w, h);
    fill(c);
    textFont(f, sz);
    textAlign(CENTER);
    text(text, x + w / 2, y + h / 1.4);
  }
}
// Un temporitzador una mica xarec però emprant 2 es pot fer pausa perfectament
class Temps {
  private int inicial = 0;
  boolean _pausa = false;
  
  int segons = 0;
  boolean pausa = false;
  
  Temps(boolean activat) {
    reiniciar(activat);
  }
  void reiniciar(boolean act) {
    inicial = millis();
    segons = 0;
    _pausa = pausa = !act;
  }
  void actualitzar() {
    if (pausa) {
      if (!_pausa) _pausa = true;
    } else {
      if (_pausa) _pausa = false;
      segons = (millis() - inicial) / 1000;
    }
  }

  String toString() {
    String min = String.format("%02d",segons / 60);
    String seg = String.format("%02d",segons % 60);
    
    return min + ":" + seg;
  }
}
// El típic que surt als jocs quan reps punts que surten i se'n van cap adalt (mijor jugar-hi per veure-ho)
class Labelpunts {
  int X, Y, sz = 22;
  int vida = 200;
  String texte;
  color c = color(255);
  
  Labelpunts(String t) {texte = t;}
  
  void actualitzar() {
    if (vida >= 4) {
      vida -= 4;
      Y -= 3;
    }
  }
  void render() {
    textFont(font, sz);
    fill(c, vida);
    noStroke();
    textAlign(CENTER);
    
    text(texte, X, Y);
  }
}
