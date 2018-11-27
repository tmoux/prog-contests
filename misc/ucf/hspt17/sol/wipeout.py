from heapq import heappush, heappop

INF = 1000000000 # arbitrary big number

T = int(input()) # read number of test cases

for t in range(1, T+1):
	line = input().split(' ') # read whole line
	n = int(line[0]) # set n
	m = int(line[1]) # set m
	s = int(line[2]) # set s

	adj = [] # initialize an adjacency list
	for i in range(n):
		adj.append([]) # make it 2 dimensional
	for i in range(m):
		arr = list(map(int, input().split(' ')))
		# store edge from i to j as a tuple (j, dist, time)
		adj[arr[0]-1].append((arr[1]-1, arr[2], arr[3])) 

	#initialize a 2-D time array representing the shortest amount of time
	# it takes to reach index i with stamina j (represented by time[i][j]
	time = []
	for i in range(n):
		time.append([])
		for j in range(s+1):
			time[i].append(INF)

	#initialize priority queue by starting with S stamina, time = 0, and at index 0
	start = (0,s,0)
	time[0][s] = 0
	pq = []
	heappush(pq,start)
	
	finalTime = INF

	# From here we run standard Dijkstra's algorithm
	while len(pq) != 0:
		node = heappop(pq)
		
		# if at the final platform and time is bettery than our best time, update best
		if(node[2] == n-1 and node[0]<finalTime):
			finalTime = node[0]

		# if we've been to this platform with this stamina before, with less time, just skip it
		if time[node[2]][node[1]] < node[0]:
			continue
		
		# go through all possible obstacles leaving this platform
		for i in adj[node[2]]:
			tS = node[1]-i[1]
			if(tS < 0):
				continue
			newTime = node[0]+i[2]
			
			# if taking this obstacle takes us to the next platform in less time, 
			# take the edge and add it to our priority queue.
			if(time[i[0]][tS] > newTime):
				time[i[0]][tS] = newTime
				heappush(pq,(newTime,tS,i[0]))

	ans = str(finalTime) if finalTime < INF else 'Wipeout!'
	print('Episode #'+str(t)+': '+ans)


