let b = "", c = "", max = 30, w = 600 / max, borrar = false, corre = false, ruta = [[0]];

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
	if (corre) {
		if (b[0] == 'W' || b[b.length - 1] == 'W') alert("No té sortida");
		else {
			let bucle = true;
			if (!sortida()) {
				alert("No té sortida");
				corre = false;
				return;
			}
			while (ruta.length > 1 || bucle) {
				for (let i = 0; i < ruta.length; i++) {
					let l = ruta[i][ruta[i].length - 1], l2 = _p(l), val = [];
					console.log(l);
					console.log(l2);
					if (l2[0] + 1 < max && b[l2[0] + 1] == '.') {
						ruta[i].push(l + 1);
						val.push(l + 1);
						//console.log("E");
					}
					if (l2[0] && b[l - 1] == '.') {
						ruta.push([l - 1]);
						val.push(l - 1);
						//console.log("O");
					}
					if (l + max < b.length && b[l + max] == '.') {
						ruta.push([l + max]);
						val.push(l + max);
						//console.log("S");
					}
					if (l - max >= 0 && b[l - max] == '.') {
						ruta.push([l - max]);
						val.push(l - max);
						//console.log("N");
					}
					let supr = [];
					val.forEach((x, i1) => {
						ruta.forEach((x2, i2) => {
							if (i2 != i && x2.indexOf(x)) supr.push(i2);
						});
					});
					console.log(ruta);
					supr.forEach((x) => ruta.splice(x, 1));
					bucle = false;
					console.log(ruta);
				}
			}
		}
		corre = false;
	}
	if (mouseX < 601 && mouseY < 601 && mouseX >= 0 && mouseY >= 0) {
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
/////////////////////////
function borrar_click() {borrar = true}
function comprovar_click() {corre = true}

function sleep(milliseconds) {
  var start = new Date().getTime();
  while (1)
    if ((new Date().getTime() - start) > milliseconds) return;
}

function sortida() {  
  b = b.r(0, 't');

  for (let i = 0; i < b.length; i++) {
    let lf = false, top = false, p = _p(i);
    if (b[i] == 't') {
      if (p[0] + 1 < w && b[i + 1] == '.') b = b.r(i + 1, 't');
      if (i + max < b.length && b[i + max] == '.') b = b.r(i + max, 't');
      if (p[0] && b[i - 1] == '.') {
        b = b.r(i - 1, 't');
        lf = true;
      }
      if (i >= max && b[i - max] == '.') {
        b = b.r(i - max, 't');
        top = true;
      }
      if ((lf && top) || top) i -= (max + 1);
      else if (top) i -= 2;
    }
  }
  console.log(b);
  let r =  b[b.length - 1] == 't';
  b = b.replace(/t/g, '.');
  return r;
}


String.prototype.r = function(i, r) {return this.substr(0, i) + r + this.substr(i + 1)}