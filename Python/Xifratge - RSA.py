'''
ALGORISME RSA:
^^^^^^^^^^^^^^
Xifrar -> m^e (mod n), e és la clau pública, no 2.7180...
Desxifrar -> m^d (mod n), d és la clau privada
-----------------------
1. Triam dos primers p i q
2. Calculam n = pq
3. Calulam phi(n), que són la quantitat de nombres coprimers p i n i q i n
4. Triam e tal que 1 < e < phi(n) i e sigui coprimer amb n i phi(n)
5. Calculam d tal que de = 1 (mod phi(n))
6. Ja podem xifrar i desxifrar

Se necessita molt de temps per fer-ho, sobretot per desxifrar, però quant més grans siguin p i q, més
temps tardarà un ordinador en esdevenir quins p i q hem triat per a que sorgeixi n. Si ho fan, aleshores
podran descobrir d, atès que ja hauran pogut calcular phi(n), que és molt difícil si no se sap quins p i q generen n.

Per la fluïdesa del programa, millor triar primers menors a 1200, però és més aviat insegur
^-----------------------
Prova desxifrar el següent:
clau pública (e, n): (3893339, 3898861)
clau privada (d, n): (1686227, 3898861)
missatge: 1877951,3368568,3043667,2287394,1229550,3083963,337474,2287394,1549652,3812645,293703,293703,3812645,1608401
(per a cada caràcter farà el següent: c^d (mod n), on c és el caràcter (en format numèric))
'''

import math
import msvcrt # getch()
import os # clear console
import re # expressions regulars

# algorisme d'Euclides ampliat per la solució particular de l'equació diofàntica ax + by = mcd(a, b)
def euclides(a, b):
    x0, x1, y0, y1 = 1, 0, 0, 1
    while a != 0:
        q, b, a = b // a, a, b % a
        x0, x1 = x1, x0 - q * x1
        y0, y1 = y1, y0 - q * y1
    return x0, y0

def getch(): return msvcrt.getch() # agafam getch() de <stdio.h> (es converteix a string de bytes)

# comprovar si un nombre és primer
def primer(n):
		if n == 2: return True
		if not n % 2: return False
		for x in range(3, int(math.sqrt(n) + 1), 2): # és suficient calcular fins la seva arrel quadrada
			if x > 1 and not n % x: return False
		return True

#calcular si dos nombres són primers entre ells (cap factor en comú)
def coprimer(a, b): # sabem que a < b
	while b:
	    mcd = b
	    b = a % b
	    a = mcd
	return mcd == 1

# Demanar l'entrada de l'usuari (sempre necessitam un nombre) fins que compleixi una certa condició (call, que és una funció)
def triar(t, call):
	d = 0
	try: d = int(input(t))
	except ValueError: return triar(t, call) # en cas de no poder convertir string a int
	return d if call(d) else triar(t, call) # tornar a cridar la funció si no es compleix la condició

phi = lambda p,q: (p - 1) * (q - 1) # funció phi(n) d'Euler en funció de p i q essent nombres primers

# començament del programa
while 1:
	print("Selecciona:\n1 => Generar claus\n2 => Xifrar\n3 => Desxifrar")
	opt = getch();
	getch(); # esperam a que l'usuari presioni un mode
	os.system("cls") # esborram la consola

	if opt == b'1':
		# generar claus
		print("GENERADOR DE CLAUS (per fluïdesa, triar p, q < 1500)")
		p = triar("Escriu p: ", primer) # demanar un nombre fins que sigui primer
		print("p = " + str(p) + "\n")

		q = triar("Escriu q: ", primer) # demanam l'atre nombre primer
		n = p * q
		ph = phi(p, q)

		print("p = " + str(p))
		print("q = " + str(q))
		print("n = " + str(n))
		print("phi({0}) = {1}".format(n, ph))
		print("\n")

		# calculam diverses possibilitats per e
		arr = []
		for x in range(2, ph):
			if coprimer(x, ph) and coprimer(x, n): # e ha de ser coprimer amb phi(p,q) i n
				arr.append(x)
			if len(arr) > 1000: break

		e = None
		if len(arr) == 1: # si e només pot ser un valor, serà aquell
			e = arr[0]
			print("e = " + str(e))
		elif not len(arr): print("Aquests paràmetres no se poden usar") # en cas de no poder usar cap valor per e (si són primers petits o repetits)
		else: # l'usuari tria manualment e donats els possibles valors
			print(arr)
			print("Tria e (ha d'estar entre aqueixos valors): ")

			e = triar("e = ", lambda x: x in arr) # demanam a l'usuari fins que hi sigui a l'array
		if len(arr):
			x = e
			d = 1

			d = euclides(e, ph)[1] # calculam d, necessitam euclides per resoldre \de = 1 (mod ph) => de + k(ph) = gcd(d, ph) = 1 (són coprimers)\
			if d <= 0: d += ph # si el mòdul és negatiu, el posam positiu (gràcies a què \x = n + x (mod n)\)

			print("d = " + str(d))	
			print("\n---------------\n")
			# imprimim les claus per a ser apuntades
			print("Clau pública: ({0}, {1})\nClau privada: ({{{2}, {3}, {4}, {5}, ...}}, {6})".format(e, n, d, d + ph, d + 2 * ph, d + 3 * ph, n))
		getch()
	elif opt == b'2':
		# encriptar
		print("XIFRAT")
		e = triar("Escriu l'exponent de xifrat (e) (clau pública): ", lambda x: True) # introduïm e (no necessitam cap condició [llevat de ser int], per tant, lambda sempre ens haurà de tornar true)
		n = triar("El mòdul (n): ", lambda x: True) # introduïm el mòdul (n)
		msg = input("Escriu el missatge: ") # el missatge
		print("\n")
		nou , l = [], len(msg)

		lletres = {} # en cas de repetir lletres, no farà falta calcularla un pic més
		it = 0
		for ch in msg: # recorrem el missatge
			if ch not in lletres.keys(): # si aquella lletra no l'hem calculada prèviament, ho farem \ch^e (mod n)\
				result = str(ord(ch) ** e % n)
				lletres[ch] = result
				nou.append(result)
			else: nou.append(lletres[ch])
			# mostram el percentatge (ja que amb claus grans és un procés lent)
			it += 1
			print("{}%".format(round(100 * it / l, 2)))

		print("\nMissatge xifrat (copiar la seqüència de números per desxifrar:\n" + ",".join(nou) + "\n" + "".join([chr(int(x)) for x in nou])) # mostram el text xifrat
		getch()

	elif opt == b'3':
		#desencriptar
		print("DESXIFRAT")
		msg = 0
		
		# inserim la clau privada
		d = triar("Escriu l'exponent de desxifrat (d) (clau privada): ", lambda x: True)
		n = triar("El mòdul (n): ", lambda x: True)
		print("Escriu el missatge (xifrat) (escriu fins que sigui com \"a, b, c, ...\"): ")
		while 1:
			msg = input("")
			# demanam el missatge numèric (per evitar problemes amb unicode) mentre no compleixi l'expressió regular (a, b, c, ...)
			if re.search(r'^(\d+)|([0-9\s]+\,[0-9\s]+)$', msg): break
		
		# separan
		msg = msg.replace(" ", "").split(',')
		nou = []
		it, l = 0, len(msg)
		print("\n")

		lletres = {} # per evitar calcular la mateixa lletra dues vegades
		for x in msg:
			num = int(x)
			if num not in lletres.keys():
				result = str((num ** d) % n) # si no l'hem calculada prèviament, feim \x^d (mod n)\
				lletres[num] = result
				nou.append(result)
			else: nou.append(lletres[num])
			# imprimim el percentatge (normalment és més lent que xifrar)
			it += 1
			print("{}%".format(round(100 * it / l, 2)))
		
		# mostram el missatge desxifrat
		print("\nMissatge desxifrat: " + ",".join(nou))
		print("".join([chr(int(x)) for x in nou]))
		getch()
	
	# esperam la tecla de l'usuari i tornam al menú
	getch() # llevar-ho si hem de pulsar dos pics la tecla
	os.system("cls")
