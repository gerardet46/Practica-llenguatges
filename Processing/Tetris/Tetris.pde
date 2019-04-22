/* Seqüència/Dinàmica del joc:
  - Caure(), cada un cert temps / Moure() -> limits amb les parets i altres peces / Girar() -> comprovar si es pot
  - Si s'ha xocat contra una peça: col·locar-la al tauler, puntuar ? esborrar fileres o no, nova peça.
  - Si no s'ha xocat contra una peça, fem el mateix pel terra, i si no tornam a començar.
  
  Tots aquests mètodes es troben a l'arxiu "mecanica.pde"
  A "peces.pde" trobarem la classe matriu, tauler i bloc (peça). Les peces les aproximarem a un cub per fer-les girar, posant-hi un 0 si no hi ha bloc
  i un 1, 2, 3 (segons el color) on hagi d'haver un bloc. El tauler es comporta de forma parescuda, només que és estàtic
  Finalment, "sis.pde" conté les classes boto, temporitzador, label pels punts, arrays, etc; el sistema en general
*/
// L'arxiu "icones.otf" servirà per incloure les icones de pausa, play, fletxes, etc. És imprescindible que es trobi a la mateixa carpeta que l'executable (o l'sketch)

boolean down = false, jugant = false, perdut = false, pausa = false, nourecord = false;
int w = 10, h = 20, y0 = 150, nivell = 1;
String[] records = new String[] {"0", "0", "0", "00:00", "00:00", "00:00"};

int punts = 0;

String PAUSA = "a";
String PLAY = "b";
String REINICIAR = "c";
String ADALT = "0";
String DRETA = "1";
String ESQUERA = "2";
String ABAIX = "3";

PFont font;
PFont icones;

Temps crono;
Temps crono1;
Boto btn1;
Boto btn2;
Boto btnfacil;
Boto btnnormal;
Boto btndificil;
Boto btnnova;

Tauler graella;
Bloc[] peces;
Bloc actual, seg;
Labelpunts label;
Labelpunts lbrecord;

static final void main(String[] args) {
  // Assignam la posició de l'aplicacio
  final String sketch = Thread.currentThread().getStackTrace()[1].getClassName();
  final String[] newArgs = append(args, "--location=500,20");
  PApplet.main(append(newArgs, sketch));
}

// A aquest mètode carregam les variables, arxius, fonts, les 7 peces, ...
void setup() {
  font = createFont("Calibri", 12);
  //icones = createFont("Calibri", 12);
  icones = createFont(sketchPath("icones.otf"), 24);
  
  btn1 = new Boto(10, 85, 55, 55, PAUSA, icones);
  btn2 = new Boto(75, 85, 55, 55, REINICIAR, icones);
  
  btnfacil = new Boto(10, 85, 120, 55, "Fàcil", font);
  btnnormal = new Boto(width / 2 - 62, 85, 124, 55, "Intermig", font);
  btndificil = new Boto(width - 130, 85, 120, 55, "Difícil", font);
  btnnova = new Boto(width / 2 - 100, 85, 200, 55, "Nova partida", font);
  
  btnfacil.defas = btnnormal.defas = btndificil.defas = btnnova.defas = y0;
  
  btn1.c = btnfacil.c = color(30, 200, 80);
  btn2.c = color(40, 100, 200);
  
  btnnormal.c = color(224, 136, 29);
  btndificil.c = color(229, 80, 80);
  btnnova.c = color(229, 226, 25);
  
  size(400, 950);
  background(20);
    
  graella = new Tauler(w, h);
  graella.sz = width / w;
  
  peces = new Bloc[7];
  
  // Configuram les 7 peces
  peces[0] = new Bloc(3);
  peces[0].dades.setFila(0, new int[] {0,0,0});
  peces[0].dades.setFila(1, new int[] {0,1,0});
  peces[0].dades.setFila(2, new int[] {1,1,1});
  
  peces[1] = new Bloc(3);
  peces[1].dades.setFila(0, new int[] {0,0,0});
  peces[1].dades.setFila(1, new int[] {2,0,0});
  peces[1].dades.setFila(2, new int[] {2,2,2});
  
  peces[2] = new Bloc(3);
  peces[2].dades.setFila(0, new int[] {0,0,0});
  peces[2].dades.setFila(1, new int[] {0,0,3});
  peces[2].dades.setFila(2, new int[] {3,3,3});
  
  peces[3] = new Bloc(3);
  peces[3].dades.setFila(0, new int[] {0,0,0});
  peces[3].dades.setFila(1, new int[] {0,4,4});
  peces[3].dades.setFila(2, new int[] {4,4,0});
  peces[3].baix = true;
  
  peces[4] = new Bloc(3);
  peces[4].dades.setFila(0, new int[] {0,0,0});
  peces[4].dades.setFila(1, new int[] {7,7,0});
  peces[4].dades.setFila(2, new int[] {0,7,7});
  peces[4].baix = true;
  
  peces[5] = new Bloc(2);
  peces[5].dades.setFila(0, new int[] {5,5});
  peces[5].dades.setFila(1, new int[] {5,5});
  
  peces[6] = new Bloc(4);
  peces[6].dades.setFila(0, new int[] {0,0,0,0});
  peces[6].dades.setFila(1, new int[] {0,0,0,0});
  peces[6].dades.setFila(2, new int[] {0,0,0,0});
  peces[6].dades.setFila(3, new int[] {6,6,6,6});
  peces[6].baix = true;
  
  for (int i = 0; i < 7; i++) {
    peces[i].X = (w - peces[i].N) / 2;
    peces[i].Y = -peces[i].N;
  }
  
  // Llegim els rècords
  String[] lect = loadStrings(sketchPath("tetris.txt"));
  if (lect == null) {
    saveStrings(sketchPath("tetris.txt"), records);
  } else {
    records = lect;
  }
  
  seg = new Bloc(peces[(int)random(7)]);
  nou();
  
  crono = new Temps(false);
  crono1 = new Temps(false);
  label = new Labelpunts("");
  lbrecord = new Labelpunts("");
}

// Aquest mètode es repetirà continuament segons la FPS triada
void draw() {
  background(20);
  translate(0, y0); // Traslladarem l'sketch a l'altura del joc per donar facilitats, però al final o haurem de tornar a posar com cal
  graella.render();
  
  botons();
  
  crono.actualitzar();
  if (jugant) {
    btn1.text = PAUSA; 
    caure();
    if (temps == 1) {
      if (xoc()) {
        int inc = -1;
        while (array0(actual.dades.fila(++inc)));
        
        if (actual.Y >= -inc) {
          afegirAlTauler();
          int files = esborrar();
          puntuar(files);
          if (nourecord) {
            records[nivell - 1] = String.format("%d", punts);
            records[nivell + 2] = crono.toString();
            saveStrings(sketchPath("tetris.txt"), records);
          } else if (punts > Integer.parseInt(records[nivell - 1])) {
            lbrecord = new Labelpunts("NOU RÈCORD!");
            lbrecord.sz = 64;
            lbrecord.Y = height / 2;
            nourecord = true;
            
            records[nivell - 1] = String.format("%d", punts);
            records[nivell + 2] = crono.toString();
            saveStrings(sketchPath("tetris.txt"), records);
          }
          nou();
        } else {
          perdut = true;
          jugant = false;
          crono.pausa = true;
        }
      } else {
        if (terra()) {
          afegirAlTauler();
          
          int files = esborrar();
          puntuar(files);
          if (nourecord) {
            records[nivell - 1] = String.format("%d", punts);
            records[nivell + 2] = crono.toString();
            saveStrings(sketchPath("tetris.txt"), records);
          } else if (punts > Integer.parseInt(records[nivell - 1])) {
            lbrecord = new Labelpunts("NOU RÈCORD!");
            lbrecord.sz = 64;
            lbrecord.Y = height / 2;
            nourecord = true;
            
            records[nivell - 1] = String.format("%d", punts);
            records[nivell + 2] = crono.toString();
            saveStrings(sketchPath("tetris.txt"), records);
          }
          nou();
        }
      }
    }
  }
  
  actual.render();
  label.actualitzar();
  label.render();
  
  // Així fem una mica de ombra, copiant el mateix texte però fosc i una mica desplaçat
  lbrecord.actualitzar();
  lbrecord.c = color(20);
  lbrecord.X = width / 2 + 5;
  lbrecord.render();
  
  lbrecord.c = color(209, 206, 5);
  lbrecord.X -= 5;
  lbrecord.render();
  
  if (perdut) {
    pantalla_negra();
    
    fill(229, 80, 80);
    textFont(font, 48);
    textAlign(CENTER);
    text("FINALITZAT!", width / 2, height / 2 - 48 * 3 + 15);
    
    fill(220);
    textFont(font, 36);
    textAlign(CENTER);
    text("Punts: " + String.format("%d", punts) + "\nTemps: " + crono.toString(), width / 2, height / 2 - 36 * 2);
    
    btnnova.y = height / 2;
    btnnova.actualitzar();
    btnnova.render();
  } else if (!jugant) {
    crono1.actualitzar();
    pantalla_negra();
    btn1.text = PLAY;
    
    textFont(font, 48);
    textAlign(CENTER);
    
    if (pausa) {
      fill(91, 183, 211);
      text("JOC PAUSAT", width / 2, height / 2 - 48 * 3 + 15);
      
      fill(220);
      textFont(font, 36);
      textAlign(CENTER);
      text("Punts: " + String.format("%d", punts) + "\nTemps: " + crono.toString(), width / 2, height / 2 - 36 * 2);
    } else {
      fill(30, 200, 80);
      text("NOVA PARTIDA", width / 2, height / 2 - 48 * 4 - 10);
      
      fill(255);
      textAlign(RIGHT);
      textFont(icones, 28);
      text("1\n3\n0\n1", width / 2 - 50, height / 2 - 28 * 5.25);
      
      textAlign(LEFT);
      textFont(font, 28);
      text("Dreta\nEsquerra\nGirar\nBaixar", width / 2, height / 2 - 28 * 5.5);
      
      textAlign(CENTER);
      text("P = Pausa, ESC = Nova partida", width / 2, height / 2 + 5);
      
      text("RÈCORDS:\nFàcil: " + records[0] + " - " + records[3] +
                    "\nIntermig: " + records[1] + " - " + records[4] +
                    "\nDifícil: " + records[2] + " - " + records[5], width / 2, height / 1.5 + 30);
      
      btnfacil.y = btnnormal.y = btndificil.y = height / 2 + 35;
      
      btnfacil.actualitzar();
      btnnormal.actualitzar();
      btndificil.actualitzar();
      
      btnfacil.render();
      btnnormal.render();
      btndificil.render();
    }    
  }
  translate(0, -y0);
  // Un pic tenim el joc "pintat", dibuixarem els botons i demés a la part superior
  
  noStroke();
  fill(20);
  rect(0, 0, width, y0); // Així amagam les peces que surten des d'amunt el tauler
  
  btn1.actualitzar();
  btn1.render();
  btn2.actualitzar();
  btn2.render();
  
  fill(220);
  textFont(font, 24);
  textAlign(LEFT);
  text("Temps: " + crono.toString(), 5, 60 - 24);
  text("Punts: " + String.format("%d", punts), 5, 60 + 12);
  
  if (jugant) {
    // Mostram la peça següent
    text("Següent",  0.7 * width, 2 * 24);
    
    Bloc r = new Bloc(seg);
    r.sz /= 1.5;
    r.X = (int)(1.5 * (w - 2.5));
    r.Y = y0 / r.sz - r.N;
    r.render();
  }
}

// Codis per a quan pressionam tecles
void keyPressed() {
  if (jugant) {
    if (keyCode == UP) {
        Bloc temp = new Bloc(actual);
        actual.dades.gir90();
        actual.baixar();
        limits(LEFT);
        limits(RIGHT);
        if (solapa()) {
          // En cas que no es pugui girar per manca d'espai,
          // tornam a la posició en què estava
          actual = new Bloc(temp);
        }
    } else if (keyCode == RIGHT) {
        dreta();
        limits(RIGHT);
    } else if (keyCode == LEFT) {
        esquerra();
        limits(LEFT);
    } else if (keyCode == DOWN) {
        max_temps = 7;
        if (temps > max_temps) temps = 2;
    }
  }
  if (key == 'p' || key == 'P') {
    if (!perdut) {
      if (btn1.text == PLAY && pausa) {
        btn1.text = PAUSA;
        crono.pausa = pausa = false;
        jugant = true;
        
        crono.actualitzar();
        crono1.actualitzar();
        
        crono.inicial += (millis() - crono1.inicial);
        crono1.pausa = true;
      } else if (btn1.text == PAUSA){
        btn1.text = PLAY;
        jugant = false;
        pausa = crono.pausa = true;
        crono1.reiniciar(true);
      }
    }
  } else if (keyCode == ESC) {
    key = 0;
    btn1.text = PAUSA;
    jugant = perdut = pausa = false;
    crono.reiniciar(false);
    crono1.reiniciar(false);
    
    graella = new Tauler(w, h);
    nou();
    
    btn2.released = false;
  }
}
void keyReleased() {
  if (keyCode == DOWN) {
     temps = max_temps = 50;
  }
}

// Els dos events següents faran que els botons detectin si han estat pijats o no, a més de la posició del cursor
void mousePressed() {
  if (mouseButton == LEFT) {
    down = true;
  }
}
void mouseReleased() {
  down = false;
}
void pantalla_negra() {
  noStroke();
  fill(0, 160);
  rect(0, 0, width, height);
}

// Event per quan fem click a un boto, és a dir, si tenen el camp released = true, que just després el posarem false
void botons() {
  if (btn1.released) {
    if (!perdut) {
      if (btn1.text == PLAY && pausa) {
        btn1.text = PAUSA;
        crono.pausa = pausa = false;
        jugant = true;
        
        crono.actualitzar();
        crono1.actualitzar();
        
        crono.inicial += (millis() - crono1.inicial);
        crono1.pausa = true;
      } else if (btn1.text == PAUSA){
        btn1.text = PLAY;
        jugant = false;
        pausa = crono.pausa = true;
        crono1.reiniciar(true);
      }
    }
    btn1.released = false;
  } else if (btn2.released) {
    btn1.text = PAUSA;
    jugant = perdut = pausa = false;
    crono.reiniciar(false);
    crono1.reiniciar(false);
    
    graella = new Tauler(w, h);
    nou();
    
    btn2.released = false;
  } else if (pausa == jugant == perdut == false) {
    // Pels nivells de dificultat, és suficient amb afegir peces al començament del joc, cosa que no farem amb el mode fàcil
    // La funció que deixa caure i mou peces automàticament s'anomena "automatic(DIRECCIO)" (nom molt original), i es trboba a "mecanica.pde"
    if (btnfacil.released) {
      nivell = 1;
      punts = 0;
      graella = new Tauler(w, h);
      pausa = perdut = false;
      jugant = true;
      
      btnfacil.released = false;
      crono.reiniciar(true);
    } else if (btnnormal.released) {
      nivell = 2;
      punts = 0;
      graella = new Tauler(w, h);
      
      // Afegim fins a tenir fileres ocupades
      automatic(RIGHT);
      nou();
      int anterior = RIGHT;
      while (array0(graella.dades.fila(13))) {
        anterior = anterior == RIGHT ? LEFT : RIGHT;
        automatic(anterior);
        nou();
      }
      
      pausa = perdut = false;
      jugant = true;
      
      btnnormal.released = false;
      crono.reiniciar(true);
    } else if (btndificil.released) {
      nivell = 3;
      punts = 0;
      
      graella = new Tauler(w, h);
      
      // Afegim fins a tenir fileres ocupades
      automatic(RIGHT);
      nou();
      int anterior = RIGHT;
      while (array0(graella.dades.fila(8))) {
        anterior = anterior == RIGHT ? LEFT : RIGHT;
        automatic(anterior);
        nou();
      }
      
      pausa = perdut = false;
      jugant = true;
      
      btndificil.released = false;
      crono.reiniciar(true);
    }
  } else if (perdut && btnnova.released) {
    perdut = jugant = pausa = false;
    
    btnnova.released = false;
  }
}
