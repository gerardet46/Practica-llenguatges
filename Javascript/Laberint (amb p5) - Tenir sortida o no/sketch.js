let b = "", c = "", max = 30, w = 600 / max, current = null;

function setup() {
	createCanvas(601,601);
	background(230);

	for (let x = 0; x <= max; x++) {
		line(0, x * w, 600, x * w);
		line(x * w, 0, x * w, 600);
	}
	for (let i = 0; i < max * max; i++) b += '.';
	c = b;
}
let borrar = false, corre = false, ind = -1;
function draw() {
	if (borrar) {
		fill(230);
		for (let i = 0; i < b.length; i++) {
			if (b[i] == 'W') {			
				let p = _p(i);
				rect(p[0] * w, p[1] * w, w, w);
			}
		}
		b = "";
		for (let i = 0; i < max * max; i++) b += '.';
		c = b;
		borrar = false;
		if (corre) window.location.href = window.location.href;
	}
	else if (corre) {
		if (b[0] == 'W' || b[b.length - 1] == 'W') {
			corre = false;
			alert("No té sortida");
		} else if (++ind <= max * max) {
			if (ind % max == 0) console.log(ind);
			if (ind == max * max) {
				if (b[b.length - 1] == 't') alert("Sortida trobada, reiniciant en 5s");
				else alert("No té sortida, reiniciant en 5s");
				sleep(5000);
				window.location.href = window.location.href
				return;
			} if (ind == 0) {
				fill(200,20,80);
				b = b.r(0, 't');
				rect(0,0,w,w);
			}
			if (b[ind] == 't') {
				if (b[b.length - 1] == 't') {
					alert("Sortida trobada, reiniciant en 5s");
					sleep(5000);
					window.location.href = window.location.href
					return;
				}
				fill(200,20,80);
				
				let p = _p(ind), po = null, lf = false, top = false;
				if (p[0] + 1 < max && b[ind + 1] == '.') {
					b = b.r(ind + 1, 't');
					po = _p(ind + 1);
					rect(po[0] * w, po[1] * w, w, w);
				}
				if (ind + max < max * max && b[ind + max] == '.') {
					b = b.r(ind + max, 't');
					po = _p(ind + max);
					rect(po[0] * w, po[1] * w, w, w);
				}
				if (p[0] && b[ind - 1] == '.') {
					b = b.r(ind - 1, 't');
					po = _p(ind - 1);
					rect(po[0] * w, po[1] * w, w, w);
					lf = true;
				}
				if (ind - max >= 0 && b[ind - max] == '.') {
					b = b.r(ind - max, 't');
					po = _p(ind - max);
					rect(po[0] * w, po[1] * w, w, w);
					top = true;
				}
				if ((top && lf) || top) ind -= (max + 1);
				else if (lf) ind -= 2;
			}
		}
	}
	else if (mouseX < 601 && mouseY < 601 && mouseX >= 0 && mouseY >= 0) {
		let a = _i(~~(mouseX / w), ~~(mouseY / w));

		if (!mouseIsPressed) current = null;
		if (current != a && mouseIsPressed) {
			if (b[a] == '.') b = b.r(a, 'W');
			else b = b.r(a, '.');

			current = a;
		}
		for (let i = 0; i < b.length; i++) {
			if (b[i] == 'W' && c[i] == '.') {
				fill(80);
				let p = _p(i);
				rect(p[0] * w, p[1] * w, w, w);
				c = b;
			}
			if (b[i] == '.' && c[i] == 'W') {
				fill(230);
				let p = _p(i);
				rect(p[0] * w, p[1] * w, w, w);
				c = b;
			}		
		}
	}
}
function _i(x, y) {return y * max + x}
function _p(i) {
	let y = 0;
	while (i >= max && ++y) i -= max;
	return [i, y];
}
///////////////////////////////////
function borrar_click() {borrar = true}
function comprovar_click() {corre = true}

function sleep(milliseconds) {
  var start = new Date().getTime();
  while (1)
    if ((new Date().getTime() - start) > milliseconds) return;
}

String.prototype.r = function(i, r) {return this.substr(0, i) + r + this.substr(i + 1)}