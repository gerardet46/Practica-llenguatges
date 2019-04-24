float pixelX(float val) {
  return map(val, -1, 1, 0, width);
}
float pixelY(float val) {
  return map(val, -1, 1, height, 0);
}

class Punt {
  float x, y, b;
  int t = 0;
  
  Punt() {
    x = random(-1, 1);
    y = random(-1, 1);
    b = 1;
  }
  Punt(float x, float y) {
    this.x = x;
    this.y = y;
    this.b = 1;
  }
  void render() {
    stroke(20);
    if (y < f(x)) {
      fill(70, 100, 150);
      t = 1;
    }
    else {
      fill(255);
      t = -1;
    }
    
    ellipse(pixelX(x), pixelY(y), 24, 24);
  }
}

class Perceptron {
  float[] pes;
  float lr = 0.01;
  
  float func(float x) {
    return -x * pes[0] / pes[1] - pes[2] / pes[1];
  }
  
  Perceptron(int N) {    
    pes = new float[N];
    for (int i = 0; i < N; i++) {
      pes[i] = random(-1, 1);
    }
  }
  
  int comprova(float[] inp) {
    float suma = 0;
    for (int i = 0; i < inp.length; i++) suma += inp[i] * pes[i];
    
    return suma >= 0 ? 1 : -1;
  }
  
  void entrenar(float[] inp, int r) {
    int res = comprova(inp);
    int error = r - res;
    
    for (int i = 0; i < pes.length; i++) {
      pes[i] += error * inp[i] * lr;
    }
  }
  void linia() {
    float[] a = {-1, func(-1), 1, func(1)};   
    line(pixelX(a[0]), pixelY(a[1]), pixelX(a[2]), pixelY(a[3]));
  }
}
