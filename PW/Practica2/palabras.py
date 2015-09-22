import random
import string

def devPalabras(fichero):
	f=open(fichero, "rt")
	retorno=f.readlines()
	return retorno

def seleccionaElemento(lista):
	return random.choice(lista)
def introLetra():
	letra=raw_input("Introduce una letra: ")
	while len(letra)!=1 or letra.isdigit():
		letra=raw_input("Introduce una letra: ")
	return letra

def buscaLetra(letra, cadena):
	lista=[]
	posicion=0
	for i in cadena:
		if i==letra:
			lista.append(posicion)
		posicion+=1
	return lista

def crearPista(palabra):
	pista=[]
	for i in range(0,len(palabra)):
		pista+='-'
	return pista

fich=raw_input("Di el nombre del fichero: ")
palabras=devPalabras(fich)
palabra=seleccionaElemento(palabras)
#letra=introLetra()
pista=crearPista(palabra)
print palabras
print palabra
print pista
