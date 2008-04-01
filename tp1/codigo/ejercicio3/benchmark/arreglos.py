import random
moda=5
for i in range(1,1000):
    x=[0]*i
    y = random.sample( range(i), i/2+1)
    for j in range(i):
        if j in y:
            x[j] = moda
        else:
            x[j] = random.randint(0,10)
    print i
    for each in range(i):
        print x[each]," ",
    print ""
print 0

