import sys

if len(sys.argv)==3:
	if int(sys.argv[1])%int(sys.argv[2])==0:
		print True
	else:
		print False
else:
	print "Argumentos mal: <programa><num1><num2>"