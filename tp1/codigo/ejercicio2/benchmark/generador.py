import random

for n in range(1,30):
	print "Caso"
	print n," ",
	print 200
	x=[[0,0] for i in range(n)]
	for i in range(n-1):
		x[i][0] = 1
		x[i][1] = 1
		print x[i][0], " ", x[i][1]
        print 200," ",200
print "Fin"
