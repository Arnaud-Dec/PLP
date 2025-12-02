
def addition():
    addition = lambda x, y: x + y 
    resultat = addition(3, 4)
    print(resultat)

def lamMap():
    nombres = [1, 2, 3, 4] 
    carres = list(map(lambda x: x ** 2, nombres))
    print(carres)

def externe(x): 
	def interne(y): 
		return y
	return interne

closure1 = externe(5)
closure2 = externe(10)
print(closure1(3)) # Affiche 8 
print(closure2(3)) # Affiche 13