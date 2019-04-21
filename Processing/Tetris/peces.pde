/* Aclaració:
Quan vaig dissenyar el joc (21/04/2019) només sabia que les matrius eren un conjunt de números i ja, però fent dibuixos me'n vaig adonar que
ho podia representar com a tal, i fer girs. Per exemple, la peça T es pot representar:
1  1  1
0  1  0
0  0  0
*/
class Matriu {
  int N, M;
  int[] dades = new int[4096];

  Matriu(int n, int m) {
    N = n;
    M = m;
    for (int i = 0; i < N * M; i++) dades[i] = 0;
  }
  void copiar(Matriu m) {
    N = m.N;
    M = m.M;
    for (int i = 0; i < N * M; i++) dades[i] = m.dades[i];
  }

  int[] col(int i) {
    int[] r = new int[M];
    for (int x = 0; x < M; x++) r[x] = dades[M * x + i];
    return r;
  }
  int[] fila(int i) {
    int[] r = new int[N];
    for (int x = 0; x < N; x++) r[x] = dades[i * M + x];
    return r;
  }
  int val(int x, int y) {
    return dades[M * y + x];
  }
  /*******************/
  void setCol(int i, int[] vals) {
    for (int x = 0; x < M; x++) dades[M * x + i] = vals[x];
  }
  void setFila(int i, int[] vals) {
    for (int x = 0; x < N; x++) dades[M * i + x] = vals[x];
  }
  void setVal(int x, int y, int val) {
    dades[N * y + x] = val;
  }
  void gir90() {
    Matriu m = new Matriu(N, M);
    for (int x = 0; x < M; x++)
      for (int y = 0; y < N; y++)
        m.setVal(y, N - 1 - x, val(x, y));
    copiar(m);
  }
}
class Tauler {
  int N, M;
  int X = 0, Y = 0;
  int sz = width / w; // Tamany per al render
  Matriu dades;
  
  boolean fons = true;

  Tauler(int n, int m) {
    N = n;
    M = m;
    dades = new Matriu(N, M);
  }

   void render() {
    // 0 -> transparent
    // 1 -> verd
    // 2 -> blau
    // 3 -> groc
    // 4 -> vermell
    // 5 -> lila
    // 6 -> taronja
    // 7 -> blau celest
    
    if (fons) {
      strokeWeight(2);
      stroke(60);
      fill(80);
      rect(sz * X, sz * Y, sz * N, sz * M);
    }
    stroke(70);
    
    
    for (int i = 0; i < M; i++) {
      int[] fila = dades.fila(i);
      for (int j = 0; j < fila.length; j++) {
        if (fila[j] != 0) {
          fill(0);
          noStroke();
          rect(sz * (X + j) + 2, sz * (Y + i) + 2, sz + 3, sz + 3);
        }
      
        switch (fila[j]) {
          case 1: fill(/*26, 188, 15*/30, 200, 80); break;
          case 2: fill(32, 68, 214); break;
          case 3: fill(229, 226, 25); break;
          case 4: fill(229, 80, 80); break;
          case 5: fill(193, 40, 204); break;
          case 6: fill(224, 136, 29); break;
          case 7: fill(91, 183, 211); break;
        }
        
        if (fila[j] != 0) {
          stroke(40);
          rect(sz * (X + j), sz * (Y + i), sz, sz);
        }
      }
    }
  }
}
// Les peces són com el tauler però dinàmiques i quadrades (encara que l'usuari no ho vegi)
class Bloc extends Tauler {
  boolean baix = false;
  Bloc(int n) {
    super(n, n);
    fons = false;
  }
  Bloc(Bloc altre) {
    super(altre.N, altre.N);
    dades.copiar(altre.dades);
    for (int i = 0; i < dades.N; i++) {
      for (int j = 0; j < dades.N; j++) {
        dades.setVal(i, j, dades.val(i, j));
      }
    }
    fons = false;
    baix = altre.baix;
    X = altre.X;
    Y = altre.Y;
  }
  
  @Override
  void render() {
    super.render();
  }
  
  void baixar() {
    if (!baix) return;
    while (array0(dades.fila(N - 1))) {
      for (int i = N - 1; i > 0; i--) {
        dades.setFila(i, dades.fila(i - 1));
      }
      dades.setFila(0, creararray(N, 0));
    }
  }
}
