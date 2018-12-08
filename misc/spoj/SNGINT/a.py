T = int(input())
for a in range(T):
    N = int(input())
    if N < 10:
    	if N == 0:
    		N = 10
    	print(N)
    else:
    	L = []
    	for i in reversed(range(10)):
    		if i == 1:
    			break
    		while N % i == 0:
    			L.append(i)
    			N = N // i
    	if N > 1:
    		print("-1")
    		
    	else:
    		for i in reversed(L):
    			print(i,end="")
    		print("")