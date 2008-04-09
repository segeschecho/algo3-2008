import random

for n in range(1,50):
	print "Caso"
	print n," ",
	print 200
	x=[[0,0] for i in range(n)]
	for i in range(n):
		x[i][0] = random.randint(1,100)
		x[i][1] = random.randint(1,100)
		print x[i][0], " ", x[i][1]
print "Fin"
