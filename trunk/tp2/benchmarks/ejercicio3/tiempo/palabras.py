import random
print 500

letras = ['a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z']
for i in range(999501,1000001):
    x=random.randint(0,len(letras)-1)
    s=""
    for j in range(i):
        s+=str(letras[(x+j) % len(letras)])
    print s

        
        
