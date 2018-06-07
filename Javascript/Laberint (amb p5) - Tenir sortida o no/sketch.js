let b = "", c = "", max = 30, w = 600 / max, current = null;

function setup() {
	createCanvas(601,601);
	background(230); // Posam com a color de fons un gris clar (#)

	for (let x = 0; x <= max; x++) { // Dibuixam les línees de separació
		line(0, x * w, 600, x * w);
		line(x * w, 0, x * w, 600);
	}
	for (let i = 0; i < max * max; i++) b += '.'; // '.' és un espai en blac i 'P' és una paret
	c = b;
}
let borrar = false, corre = false, ind = -1;
function draw() {
	if (borrar) {
		// Borram
		fill(230);
		for (let i = 0; i < b.length; i++) {
			if (b[i] == 'p') {			
				let p = _p(i);
				rect(p[0] * w, p[1] * w, w, w);
			}
		}
		b = "";
		for (let i = 0; i < max * max; i++) b += '.';
		c = b;
		borrar = false;
		if (corre) window.location.href = window.location.href; // Actualitzar la pàgina
	}
	else if (corre) {
		if (b[0] == 'p' || b[b.length - 1] == 'p') { // Si comença o acaba amb un mur, no té sortida
			corre = false;
			alert("No té sortida");
		} else if (++ind <= max * max) { // ja que draw() s'executa infinitament, usar ++ind és com fer un bucle del tipus for, però així podrem veure com evoluciona l'algoritme
			if (ind % max == 0) console.log(ind);
			if (ind == max * max) { // Hem acabat
				if (b[b.length - 1] == 't') alert("Sortida trobada, reiniciant en 5s");
				else alert("No té sortida, reiniciant en 5s");
				sleep(5000);
				window.location.href = window.location.href;
				return;
			} if (!ind) { // Si l'index és 0, posam la primera casella seleccionada (punt de partida)
				fill(200,20,80); // Fúcsia (més vermell que blau, i aquest més que verd)
				b = b.r(0, 't');
				rect(0,0,w,w);
			}
			if (b[ind] == 't') { // Si podem continuar a partir de la casella, n'afegirem més segons si està buida
				if (b[b.length - 1] == 't') {
					alert("Sortida trobada, reiniciant en 5s");
					sleep(5000);
					window.location.href = window.location.href
					return;
				}
				fill(200,20,80);
				
				let p = _p(ind), po = null, lf = false, top = false;
				if (p[0] + 1 < max && b[ind + 1] == '.') { // veïna de la dreta
					b = b.r(ind + 1, 't');
					po = _p(ind + 1);
					rect(po[0] * w, po[1] * w, w, w);
				}
				if (ind + max < max * max && b[ind + max] == '.') { // veïna del sud
					b = b.r(ind + max, 't');
					po = _p(ind + max);
					rect(po[0] * w, po[1] * w, w, w);
				}
				if (p[0] && b[ind - 1] == '.') { // A l'esquerra
					b = b.r(ind - 1, 't');
					po = _p(ind - 1);
					rect(po[0] * w, po[1] * w, w, w);
					lf = true;
				}
				if (ind - max >= 0 && b[ind - max] == '.') { // Al nord
					b = b.r(ind - max, 't');
					po = _p(ind - max);
					rect(po[0] * w, po[1] * w, w, w);
					top = true;
				}
				// Retrocedim si hem pogut anar a l'esquerra o adalt
				if ((top && lf) || top) ind -= (max + 1);
				else if (lf) ind -= 2;
			}
		}
	}
	else if (mouseX < 601 && mouseY < 601 && mouseX >= 0 && mouseY >= 0) {
		let a = _i(~~(mouseX / w), ~~(mouseY / w)); // Obtenim la cel·la en la què estam

		if (!mouseIsPressed) current = null;
		// Pintam o despintam la cel·la actual (current)
		if (current != a && mouseIsPressed) {
			if (b[a] == '.') b = b.r(a, 'p');
			else b = b.r(a, '.');

			current = a;
		}
		for (let i = 0; i < b.length; i++) {
			if (b[i] == 'p' && c[i] == '.') {
				fill(80);
				let p = _p(i);
				rect(p[0] * w, p[1] * w, w, w);
				c = b;
			}
			if (b[i] == '.' && c[i] == 'p') {
				fill(230);
				let p = _p(i);
				rect(p[0] * w, p[1] * w, w, w);
				c = b;
			}		
		}
	}
}
function _i(x, y) {return y * max + x} // Punt a sencer
function _p(i) { // Nombre enter a punt
	let y = 0;
	while (i >= max && ++y) i -= max;
	return [i, y];
}
///////////////////////////////////
function borrar_click() {borrar = true}
function comprovar_click() {corre = true}

function sleep(milliseconds) { // Pausar l'execució durant n mil·lèsimes
  var start = new Date().getTime();
  while (1)
    if ((new Date().getTime() - start) > milliseconds) return;
}

String.prototype.r = function(i, ch) {return this.substr(0, i) + ch + this.substr(i + 1)} // funció per reemplaçar un caràcter ch a l'index i
