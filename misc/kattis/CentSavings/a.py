line = input().split()
n = int(line[0])
d = int(line[1])
items = list(map(int, input().split()))

costs = [[-1 for i in range(d+1)] for j in range(n+1)]         

def getPrice(r,d):

    if r == 0:
      costs[0][d] = 0
      return costs[0][d]

    if costs[r][d] != -1:
    # we already computed this value so no need to recompute
        return costs[r][d]


    if(d==1):
    # base case: if one divider, return sums rounded 
        left = round(sum(items[0:r]), -1)
        right = round(sum(items[r:n]), -1)
        costs[r][0] = left + right
        return costs[r][0]
        

    mincost = sum(items[0:n])
    mincost = round(mincost, -1)
    
    left = 0
    for i in range(0, r):

        left += items[i]
        
        left_round = round(left, -1)

        right = getPrice(i+1, d-1)

        total = left_round + right
        mincost = min(mincost, total)
        
    costs[r][d] = mincost
    return costs[r][d] 

print(getPrice(n, d))
