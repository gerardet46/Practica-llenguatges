from decimal import *
import sys

sys.setrecursionlimit(int(10e7)) # per calcular factorials grans, ja que usa recursió

def fact(n):
	if n == 1:
		return n
	else:
		return n * fact(n - 1)

r = 1
c = 1
darrer = r

dec = int(input("Precisió decimal: ")) # presició decimal que volem obtenir
getcontext().prec = dec

num = ""

while num != "pi" and num != "e": # demanam si volem calcular pi o e
	num = input("Vols calcular \"e\" o \"pi\"?: ").lower()

if num == "pi": # configuram r i c en cas de triar pi, atès que estava configurat per e
	r = c = 0

while 1:
	darrer = r # establim el darrer sumand, si coincideix amb el nou, hem obtingut el nombre com cal

	# sumam els termes de la sèrie corresponent a cada nombre
	if num == "e":
		r += 1 / Decimal(fact(c))
	elif num == "pi":
		r += Decimal(Decimal((4 / (8 * c + 1) - 2 / (8 * c + 4) - 1 / (8 * c + 5) - 1 / (8 * c + 6))) / (16 ** c))

	if darrer == r: # si coincideix, mostram el resultat i el guardam a un arxiu
		print("\n------------------------------\nNombre " + num + " amb " + str(dec) +
			" decimals aconseguit (" + str(c) + " iteracions):\n" + str(r))

		file = open(num + ' - ' + str(dec) + ' digits.txt', 'w')
		file.write(str(r))
		file.close()
		print
		exit()

	if c % 100 == 0:
		print("Sumand " + str(c)) # indicam a l'usuari per quin sumand anam cada 100 que es fan

	c += 1 # proper terme de la sèrie