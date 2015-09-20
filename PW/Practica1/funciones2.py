#!/usr/bin/python
import rlcompleter, readline
readline.parse_and_bind("tab:complete")


def esDivisible(a,b):
	return a%b==0

def esDivisible2(a,b):
	if esDivisible(a,b)==True:
		print "Es divisible"
	else:
		print "No es divisible"
