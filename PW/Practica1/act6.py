x=1
while x<=10:
	print "Tabla del "+str(x)
	print "-------------"
	y=1
	while y<=10:
		producto= int(x)*int(y)
		print "\t"+str(x)+" * "+str(y)+" = "+ str(producto)
		y+=1
	x+=1