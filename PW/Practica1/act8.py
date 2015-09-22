
lista=raw_input("Introduce una serie de caracteres alfanumericos: ").split()
lista2=raw_input("Introduce una segunda serie de caracteres alfanumericos: ").split()
listafinal= lista+lista2
listafinal.sort()
for x in listafinal:
	while listafinal.count(x) > 1:
		listafinal.remove(x)
print listafinal
