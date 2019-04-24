// Variables:

let frase;
let frase_arr = [];
let llargada;
let poblacio = 10000;
let pob = [];
let mut_rate = 0.5;
let generacio = 0;
let acerts = -1;
let fet = false;
let max_index = [0, 0, 0];

function començar() {
  // Codi per establir la primera generació (a l'atzar)
  max_index = [0, 0, 0];

  pob = [];
  generacio = 0;
  acerts = -1;

  frase = $("#frase").text();
  llargada = frase.length;
  for (var i = 0; i < llargada; i++) frase_arr[i] = frase.charCodeAt(i);

  for (var i = 0; i < poblacio; i++) {
    pob[i] = new FRASE();
  }
}

function setup() {
  noCanvas();
  començar();
}

function draw() {
  if (fet) return;
  
  // Generam la propera generació
  // "Mating pool"
  var inc = 10000;
  if (max_index[1] > 0.35) inc /= 10;
  if (max_index[1] > 0.65) inc /= 10;
  if (max_index[1] > 0.85) inc /= 10;
  var pool = [];
  for (var i = 0; i < poblacio; i++) {
    pob[i].calc_fitness();
    pob[i].calc_fitness2();
    if (pob[i].fitness > max_index[1]) max_index = [i, pob[i].fitness, pob[i].fitness2];

    for (var j = 0; j < pob[i].fitness* pob[i].fitness * inc + 1; j++) pool.push(pob[i]);
  }

  // Crossover
  var npob = [];
  for (var i = 0; i < poblacio; i += 2) {
    var a = random(pool), b = random(pool);
    var c = new FRASE(), d = new FRASE();

    for (var j = 0; j < llargada; j++) {
      if (random(1) < mut_rate / 100) c.lletres[j] = ~~(random(1,256));
      else if (j % 2) c.lletres[j] = a.lletres[j];
      else c.lletres[j] = b.lletres[j];

      if (random(1) < mut_rate / 100) c.lletres[j] = ~~(random(1,256));
      else if (j % 2) d.lletres[j] = b.lletres[j];
      else d.lletres[j] = a.lletres[j];
    }
    npob.push(c);
    npob.push(d);
  }
  // Resultats
  $("#millors").html("Generació " + (++generacio).toString() + " -> " + pob[max_index[0]].toString() + "<br>" + $("#millors").html());
  if (generacio % 500 == 0) {
    $("#millors").html('');
  }

  var carac = ~~(max_index[2] * llargada);
  if (carac > acerts) {
    $("#adalt").text(pob[max_index[0]] + " - " + carac.toString() + "/" + llargada.toString() + " caràcters");
    acerts = carac;
  }
  
  if (pob[max_index[0]].toString() == frase) {
    fet = true;
    $("#adalt").text(pob[max_index[0]]);
  }

  pob = npob;
}

// Els gens, caracteritzats per tenir una sèrie de lletres i poder calcular acerts
function FRASE() {
  this.lletres = [];
  this.posicions = [];
  this.fitness = 0;
  this.fitness2 = 0;

  for (var i = 0; i < llargada; i++) {
    this.lletres[i] = ~~(random(1,256));
  }

  this.calc_fitness = () => {
    var suma = 0, inc = 0;
    for (var i = 0; i < llargada; i++) {
     if (this.lletres[i] == frase_arr[i]) suma += (++inc);
    }
    this.fitness = suma / (llargada * (llargada + 1) / 2);
  }
  this.calc_fitness2 = () => {
    var suma = 0;
    for (var i = 0; i < llargada; i++) {
     if (this.lletres[i] == frase_arr[i]) suma++;
    }
    this.fitness2 = suma / llargada;
  }
  this.toString = () => {
    var s = "";
    for (var i = 0; i < llargada; i++) s += String.fromCharCode(this.lletres[i]);
    return s;
  }
}
