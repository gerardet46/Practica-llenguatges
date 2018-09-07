class Joystick {
  // Varibles públiques
  float x, y, ample, pendent, angle, extra;
  PVector v, factor;
  float[] petit = new float[3];
  boolean actiu = false, quadricula = true;
  
  /**
   * Contructor de la classe Joystick (extra [factor de velocitat] = 1);
   *
   * @param  _x  La coordenada x on es situarà el Joystick
   * @param  _y  La coordenada y on es situarà el Joystick
   * @param  w  L'amplada del joystick
   * @param  w_petit  L'amplada del controlador del joystick
   */
   Joystick(float _x, float _y, float w, float w_petit) {
    // Assignam les variables
    x = _x;
    y = _y;
    v = new PVector(0, 0);
    ample = w;
    petit[0] = x;
    petit[1] = y;
    petit[2] = w_petit;
    extra = 1;
  }
  /**
   * Contructor de la classe Joystick
   *
   * @param  _x  La coordenada x on es situarà el Joystick
   * @param  _y  La coordenada y on es situarà el Joystick
   * @param  w  L'amplada del joystick
   * @param  w_petit  L'amplada del controlador del joystick
   * @param  extra  Factor a emprar per augmentar la velocitat (en principi 1)
   */
  Joystick(float _x, float _y, float w, float w_petit, float _extra) {
    // Assignam les variables
    x = _x;
    y = _y;
    v = new PVector(0, 0);
    ample = w;
    petit[0] = x;
    petit[1] = y;
    petit[2] = w_petit;
    extra = _extra;
  }
  
  /**
   * Actualitzam el Joystick (si l'estam movent, la posició, pendent, ...)
   */
  void actualitzar() {
    if (mousePressed && mouseButton == LEFT) { // Si l'estam activant
      actiu = true; // Assenyalam que el joystick està actiu
      float _x = mouseX,
            _y = mouseY,
            h = ((_y - y > 0) ? 1 : -1) * dist(_x, _y, _x, y), // Altura del controlador respecte el joystick
            l = ((_x - x > 0) ? 1 : -1) * dist(x, y, _x, y); // Distància (x) del controlador respecte el joystick
      
      pendent = (l == 0) ? 99999 : -h / l; // Pendent de la funció (cal recordar que a informàtica la y augmenta a mesura que se baixa, no com a mates
      angle = atan(abs(h / (l == 0 ? 0.00001 : l))); // Angle (només 0-90º [0-PI/2 rad])
      
      if (sq(_x - x) + sq(_y - y) > sq(ample / 2)) { // Teorema de Pitàgores: si el cursor és a fora del Joystick, posarem el controlador a la circunfèrencia
        // Ajustam la posició del controlador
        petit[0] = x + (l < 0 ? -1 : 1) * cos(angle) * ample / 2;
        petit[1] = y + (h < 0 ? -1 : 1) * sin(angle) * ample / 2;
        factor = new PVector(1, 1);
      } else {
        // Si estam dins la circunferència donada, la posició serà exactament la del cursor
        petit[0] = _x;
        petit[1] = _y;
        factor = new PVector(abs(_x - x) / (ample / 2), abs(_y - y) / (ample / 2)); // Reduïm la velocitat
      }
      // Ajustam l'angle de 0-90º a 0-360º segons l'altura i la distància al centre del joystick
      if (h > 0) {
        if (l < 0) angle += PI;
        else angle = TAU - angle;
      }
      else if (l < 0) angle = PI - angle;
      
      // Calculam les velocitats
      /* Com podem comprovar, el mòdul del vector de la velocitat |v| és sqrt(vx^2 + vy^2)
         I tenim que sqrt(extra^2*[cos^2(x)+sin^2(x)])=extra (trigonometria [sin^2 x + cos^2 x = 1]), i sin^2(x)=vx*pendent
      */
      v.x = cos(angle);
      //v.y = -sin(angle);
      v.y = -pendent * v.x; // (equivalent a l'anterior) Recordam distinció de gràfics mates-informàtica
      
      v.mult(extra);
      v.x *= factor.x;
      v.y *= factor.y;
      
      if (l == 0) v = new PVector(0, extra);
      if (l == 0 && h < 0) v.y = -v.y; // Si té un angle de 270º exactes
    } else {
      // Si no el presionam, resetejam les variables
      actiu = false;
      petit[0] = x;
      petit[1] = y;
      v = new PVector(0, 0);
    }
  }
  
  void render() {
    stroke(200);
    strokeWeight(1);
    ellipseMode(CENTER); // Molt important no canviar-ho! Molts càlculs depenen d'això
    
    // Cercle gran
    fill(180, 200);
    ellipse(x, y, ample, ample);
    
    // Punts cardinals, si volem
    if (quadricula) {
      stroke(255, 180);
      strokeWeight(2);
      line(x - ample / 3, y, x + ample / 3, y);
      line(x, y - ample / 3, x, y + ample / 3);
      fill(0, 0);
      ellipse(x, y, petit[2], petit[2]);
    }
    
    // Cercle petit (controlador)
    stroke(200);
    strokeWeight(1);
    fill(100, 180);
    ellipse(petit[0], petit[1], petit[2], petit[2]);
  }
}
