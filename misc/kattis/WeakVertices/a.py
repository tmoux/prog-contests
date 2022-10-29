from collections import defaultdict
while True:
    
    n = int(input())
    if n == -1:
        break
    graph = defaultdict(lambda:set())
    matrix = []
    
    for i in range(n):
        matrix.append(input().split())
    
    for i in range(len(matrix)):
        for j in range(len(matrix)):
            if matrix[i][j] == "1":
                graph[i].add(j)
    toRemove = set()
    for i in range(n):
        toRemove.add(str(i))
    
    for key1 in graph:
        triangle = False
        for key2 in graph[key1]:
                for key3 in graph[key2]:
                    if key1 in graph[key3]:
                        triangle = True
        if triangle == True:
            toRemove.remove(str(key1))
    
    toRemove = set(['1', '9', '10', '999'])
    print(" ".join(sorted(list(toRemove))))
