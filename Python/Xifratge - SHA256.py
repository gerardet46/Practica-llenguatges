'''
ATENCIÓ:
^^^^^^^^^^^^^^^^^^^^
Aquest algorisme no és de xifratge, sinó una funció hash, és a dir, no es pot desxifrar,
llevat de si es prova cada possibilitat fins a trobar-ne la correcte. El sistema de desxifratge
vigent funciona per força bruta, atès que no ens queda d'altra, i per tant està limitat a esdevenir
els hashos de strings amb menys de 3 caràcters. Manca de clau, ja que és un algorisme fixo, no com
l'RSA. No utilitzar l'algorisme per xifrar, sinó per tenir un hash de llongitud limitada, que ajuda
als protocols d'internet TLS i SSL, a més de Bitcoin i altres.

És la millora de MD4 i MD5, també funcions hash, però molt fàcils de trencar per col·lisió,
no com SHA-256, que a aquest programa es permet desxifrar menys de 3 caràcters.

Va molt bé per fixar la llongitut dels arxius i és molt més ràpid que RSA

Veure "http://www.iwar.org.uk/comsec/resources/cipher/sha256-384-512.pdf" per com funciona l'algorisme
'''

import math, msvcrt, os

p = [2, 3]

while len(p) < 64: # generam els 64 primers nombres primers
	x = p[len(p) - 1]
	while 1:
		x += 2
		pr = True
		for i in p:
			if not x % i:
				pr = False
				break
		if pr:
			p.append(x)
			break

frac = lambda n: int(math.modf(n)[0] * (1 << 32)) # agafam la part fraccional d'un nombre
sp = lambda s, x: [s[i:i + x] for i in range(0, len(s), x)] # separam un texte s en toços de llongitut x

############## FUNCIONS PRÒPIES DE SHA-256
S = lambda n, d: (n >> d)|(n << (32 - d));
Ch = lambda x, y, z: (x & y) ^ (~x & z)
Maj = lambda x, y, z: (x & y) ^ (x & z) ^ (y & z)
s0 = lambda x: S(x, 2) ^ S(x, 13) ^ S(x, 22)
s1 = lambda x: S(x, 6) ^ S(x, 11) ^ S(x, 25)
o0 = lambda x: S(x, 7) ^ S(x, 18) ^ (x >> 3)
o1 = lambda x: S(x, 17) ^ S(x, 19) ^ (x >> 10)

def mod32add(x, y):
	num = 0xffffffff + 1
	r = x + y
	k = math.ceil((r - num) / num)
	return r - k * num

###################################
def msg2bin(s): # Passam el missatge escrit a binari (IMPORTANT: a cada caràcter li asignam 8 bits!)
	r = ""
	for c in s:
		r += '{0:08b}'.format(ord(c))
	return r

K = [frac(math.pow(x, 1 / 3)) for x in p] # obtenim les 64 constants de SHA-256

def xifrar(msg): # Mètode de xifratge (veure PDF [link adalt])
	H = [frac(math.sqrt(x)) for x in p if p.index(x) < 8] # resetejam els hashos
	msg = msg2bin(msg) + '1' # passam l'escrit a binari i afegim un 1 al final
	l = len(msg) - 1 # llongitud del missatge inicial (en bits, no bytes)

	k = 0
	while (l + 1 + k) % 512 != 448: k += 1 # afegim k zeros fins que l + 1 + k = 448 mod 512

	msg += ('0' * k) + (bin(l)[2:].zfill(64)) # afegim el nombre de bits del missatge el final, en format de 64 bits, així aconseguim que sigui múltiple de 512

	M = [sp(x, 32) for x in sp(msg, 512)] # separam el missatge en blocks de 512 bits, i alhora aquests en subblocs de 32 bits (8 en HEX)
	for x in M:
		for y in x:
			M[M.index(x)][x.index(y)] = int(y, 2) # convertim string binari a numero (per així operar un pic tenim els blocs)

	for Mi in M: # per a cada bloc de 512 bits
		W = []		
		a, b, c, d, e, f, g, h = H[0], H[1], H[2], H[3], H[4], H[5], H[6], H[7]
		for j in range(64):
			# calculam la W que necessitarem per la variable T1
			if j < 16: W.append(Mi[j])
			else: W.append(mod32add(mod32add(mod32add(o1(W[j - 2]), W[j - 7]), o0(W[j - 15])), W[j - 16]))
			
			#  Canviam els valors
			T1 = mod32add(mod32add(mod32add(mod32add(h, s1(e)), Ch(e,f,g)), K[j]), W[j])
			T2 = mod32add(s0(a), Maj(a,b,c))
			h = g
			g = f
			f = e
			e = mod32add(d, T1)
			d = c
			c = b
			b = a
			a = mod32add(T1, T2)

		# Ara canviam els hashos inicials, que seran el resultat si els juntam
		H[0] = mod32add(a, H[0])
		H[1] = mod32add(b, H[1])
		H[2] = mod32add(c, H[2])
		H[3] = mod32add(d, H[3])
		H[4] = mod32add(e, H[4])
		H[5] = mod32add(f, H[5])
		H[6] = mod32add(g, H[6])
		H[7] = mod32add(h, H[7])

	return ["0x{:08x}".format(x)[2:] for x in H] # tornam els hashos en format hexadecimal (així s'ha de fer), de 32 bits cadascun (8 digits)

def desxifrar(hash): # desxifram a la força bruta
	if len(hash) != 64: return "El format és incorrecte (no té 64 caràcters)"
	# k serà el text que provarem, ja que els números poden ser convertits a text
	k = 0
	while k < 200000: # màxim per operar
		if not k % 3000 and k: print(k) # imprimim de tant en tant per veure el procés

		# regió per convertir de número a text (passant el número a binari)
		r = bin(k)[2:]
		while len(r) % 8: r = '0' + r
		r = sp(r, 8)
		r = "".join([chr(int(x, 2)) for x in r])
		
		if "".join(xifrar(r)) == hash: return r # si coincideix, hem trobat el resultat
		k += 1
	return "El text per desxifrar és molt gran (> 200000 [en número])"

######### COMEÇAMENT DEL PROGRAMA: demanam l'entrada de l'usuari per xifrar o desxifrar, i també el text a treballar
while 1:
	print("Selecciona:\n1 => Xifrar\n2 => Desxifrar")
	opt = msvcrt.getch()
	os.system("cls")

	if opt == b'1':
		HASH = xifrar(input("Escriu el missatge: "))
		print("\n" + "".join(HASH))
		print("\n(" + " - ".join(["0x" + x for x in HASH]) + ")\n--------------------------")

	elif opt == b'2':
		print("\nResultat: " + desxifrar(input("Escriu al has a desxifrar: ")))
		print("------------------------")

	else: os.system("cls")
	msvcrt.getch()
