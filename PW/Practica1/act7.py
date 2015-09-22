
lista=raw_input("Introduce una serie de caracteres alfanumericos: ").split()
for x in lista:
	if x.isdigit() and int(x)%2==0:
		lista.remove(x)

print "Tu lista modificada "
print lista