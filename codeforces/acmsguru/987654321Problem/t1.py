numFound = 0;
for i in xrange(100000000,1000000000):
    if (i*i % 1000000000 == 987654321):
        print(i,i*i)
        numFound += 1
print("Num Found: ",numFound)

