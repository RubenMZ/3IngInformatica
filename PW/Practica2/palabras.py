import random
import string
import os

def devPalabras(fichero):
	f=open(fichero, "rt")
	retorno=f.readlines()
	f.close()
	return retorno

def seleccionaElemento(lista):
	palabra=random.choice(lista)
	if palabra[len(palabra)-1]=='\n':
		palabra=palabra[:len(palabra)-1]
	return palabra

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
	pista="".ljust(len(palabra),'-')
	return pista

def borraRepetidas(fichero):
	f=open(fichero, "rt")
	lista=f.readlines()
	aux=[]
	for palabra in lista:
		if palabra not in aux:
			aux.append(palabra)
	f.close()
	os.remove(fichero)

	f=open(fichero, "wt")
	for palabraAux in aux:
		f.write(palabraAux)
	f.close()
	
	

fich=raw_input("Di el nombre del fichero: ")
borraRepetidas(fich)
palabras=devPalabras(fich)
print palabras
palabra=seleccionaElemento(palabras)
pista=crearPista(palabra)
print pista

fallos=0
continuar=1	

#while fallos<5:
#	letra=introLetra() 
#	listaLetra=buscaLetra(letra,palabra) 
#	for i in listaLetra: 	
#		pista=str(pista[0:i])+letra+str(pista[i+1:])
#
#	print pista 
#	if len(listaLetra)==0:
#		fallos+=1
#	print "Fallos: "+str(fallos)
#	if "-" not in pista:
#		break 


while fallos<10 and continuar==1:
	continuar=0
	letra=introLetra() 
	listaLetra=buscaLetra(letra,palabra) 
	for i in listaLetra: 	
		pista=str(pista[0:i])+letra+str(pista[i+1:])

	print pista 
	if len(listaLetra)==0:
		fallos+=1
	print "Fallos: "+str(fallos)
	for i in pista:
		if i == "-":
			continuar=1

if fallos==10:
	print "Oh has perdido"
	print "La palabra es: "+palabra
else:
	print "Ole, has ganado"