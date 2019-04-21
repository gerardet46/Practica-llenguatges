// Peça nova aleatòria (tenint en compte que ja mostram la vinent);
void nou() {
  actual = new Bloc(seg);
  seg = new Bloc(peces[(int)random(7)]);
}

int temps = 50, max_temps = 50;
// Mètode per deixar caure la peça cada un interval
void caure() {
  if (--temps == 0) {
    actual.Y++;
    temps = max_temps;
  }
}
// More a la dreta, i comprovar si és possible
void dreta() {
  actual.X++;
  limits(RIGHT);
}
// El mateix per l'altre banda
void esquerra() {
  actual.X--;
  limits(LEFT);
}
// Per a comprova si ens hem estavellat contra la paret o els blocs
boolean limits(int dir) {  
  if (dir == RIGHT) {
    // Boreres del joc (dreta)
    int out =  -(w - actual.X - actual.N);
    while (--out >= 0) {
       if (!array0(actual.dades.col(actual.N - 1 - out))) actual.X--;
    }
    
    // Si hem girat a la dreta, tornarem a l'esquerra
    for (int i = 0; i < actual.dades.N; i++) {
      for (int j = actual.dades.N - 1; j >= 0; j--) {
        if (actual.X + j < 0 || actual.Y + i < 0) continue;
        if (graella.dades.val(actual.X + j, actual.Y + i) != 0 && actual.dades.val(j, i) != 0) {
          actual.X--;
          return true;
        }
        if (!array0(actual.dades.col(j))) break;
      }
    }
  } else {
    // Boreres del joc (esquerra)
    int out = -actual.X;
    while (--out >= 0) {
       if (!array0(actual.dades.col(out))) actual.X++;
    }
    
    // Si hem girat a l'esquerra, tornarem a la dreta
    for (int i = 0; i < actual.dades.N; i++) {
      for (int j = 0; j < actual.dades.N; j++) {
        if (actual.X + j < 0 || actual.Y + i < 0) continue;
        if (graella.dades.val(actual.X + j, actual.Y + i) != 0 && actual.dades.val(j, i) != 0) {
          actual.X++;
          return true;
        }
        if (!array0(actual.dades.col(j))) break;
      }
    }
  }
  return false;
}
// Un cop la peça no caigui més, l'afegirem a la matriu del tauler
void afegirAlTauler() {
  for (int i = 0; i < actual.N; i++) {
    for (int j = 0; j < actual.N; j++) {
      int val = actual.dades.val(i, j);
      if (val != 0) {
        if (2 * (actual.Y + j) < 0) {
          perdut = true;
          jugant = false;
          return;
        }
        graella.dades.setVal(actual.X + i, 2 * (actual.Y + j), val);
      }
    }
  }
}
// Si toca el final de la graella
boolean terra() {
  int inc = 0;
  while (array0(actual.dades.fila(actual.N - (++inc))));
  
  while (actual.Y + actual.N - inc + 1 > h) actual.Y--;
  if (actual.Y + actual.N - inc + 1 == h) return true;
  
  return false;
}
// A vegades és possible que no es pugui girar per què es solapa
boolean solapa() {
  for (int i = 0; i < actual.N; i++) {
    for (int j = 0; j < actual.N; j++) {
      if (actual.X + i >= w || actual.Y + j < 0 || actual.X + i < 0) continue;
      if (actual.dades.val(i, j) != 0 && graella.dades.val(actual.X + i, actual.Y + j) != 0) {
        return true;
      }
    }
  }
  return false;
}
// Comprovam si abaix hi ha una peça, i pertant, l'acoblam al tauler
boolean xoc() {
  for (int i = 0; i < actual.N; i++) {
    for (int j = actual.N - 1; j >= 0; j--) {
      if (actual.X + i >= w || actual.Y + j + 1 < 0 || actual.X + i < 0) continue;
      if (actual.dades.val(i, j) != 0 && graella.dades.val(actual.X + i, actual.Y + j + 1) != 0) {
        return true;
      }
    }
  }
  return false;
}
// En cas que hagem completat una filera, puntuarem i esborrarem (que és aquest mètode)
int esborrar() {
  int files = 0;
  
  for (int i = 0; i < actual.N; i++) {
    if (!arr_conte(graella.dades.fila(actual.Y + i), 0)) {
      ++files;
      for (int j = actual.Y + i; j > 0; j--) {
        graella.dades.setFila(j, graella.dades.fila(j - 1));
        graella.dades.setFila(0, creararray(w, 0));     
      }
    }
  }
  
  return files;
}
// Puntuam les fileres esborrades
void puntuar(int files) {
  if (files > 0) {
    int t = 40 * nivell;
    if (files == 2) t = 100 * nivell;
    else if (files == 3) t = 300 * nivell;
    else if (files == 4) t = 1200 * nivell;
    
    label = new Labelpunts(String.format("%d", t));
    label.X = width / w * (actual.X + actual.N / 2);
    label.Y = width / w * (actual.Y + 1);
    if (label.X < 20) label.X = 20;
    if (label.Y < 10) label.Y = 10;
    punts += t;
  }
}
// Fer tot el procediment automàticament per ja començar amb una certa distribució
void automatic(int DIRECCIO) {
  while (true) {
    caure();
    int r = (int)random(9);
    int r1 = (int)random(1,4);
    int r2 = (int)random(3);
    
    if (DIRECCIO == RIGHT) {
      if (r > 5)  {
        while (--r1 >= 0) {
          dreta();
          limits(RIGHT);
        }
      }
      else if (r < 2) {
        while (--r1 >= 0) {
          esquerra();
          limits(LEFT);
        }
      }
    } else {
      if (r < 2)  {
        while (--r1 >= 0) {
          dreta();
          limits(RIGHT);
        }
      }
      else if (r > 5) {
        while (--r1 >= 0) {
          esquerra();
          limits(LEFT);
        }
      }
    }
    for (int i = 0; i < r2; i++) {
      Bloc temp = new Bloc(actual);
      actual.dades.gir90();
      actual.baixar();
      limits(LEFT);
      limits(RIGHT);
      if (solapa()) {
        actual = new Bloc(temp);
        break;
      }
    }
    if (xoc() || terra()) {
      afegirAlTauler();
      return;
    }
  }
}
