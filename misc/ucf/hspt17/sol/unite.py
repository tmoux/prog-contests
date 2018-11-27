# Returns the squared distance between two 3D points
def distSq(a, b):
    return sum((p - q) ** 2 for p, q in zip(a, b))

# Kruskal's minimum spanning forest algorithm
# Returns the cost of the minimum spanning tree
def kruskals(n, edges):
    # Make the set with each node parenting itself
    par = list(range(n))

    # Find the parent of a node
    def find(node):
        if par[node] == node:
            return node

        # Compress the path
        par[node] = find(par[node])
        return par[node]

    # Union two subtrees
    def union(a, b):
        aRoot = find(a)
        bRoot = find(b)

        par[bRoot] = aRoot

    # Build the minimum spanning tree
    mst = []
    # Sort by increasing cost
    for edge in sorted(edges, key=lambda tup: tup[2]):
        u, v, cost = edge

        # Union disjoint subtrees and add the edge to MST
        if find(u) != find(v):
            union(u, v)
            mst.append(edge)

    # Return the cost of the MST
    return sum(cost for _, _, cost in mst)


# Process each case
T = int(input())
for case in range(T):
    # Read in each location
    n = int(input())
    locs = [tuple(map(int, input().strip().split())) for _ in range(n)]

    # Build the edge list in form (u, v, cost)
    edges = []
    for u, uloc in enumerate(locs):
        for v, vloc in enumerate(locs):
            if u == v:
                continue

            edges.append((u, v, distSq(uloc, vloc)))

    # Run Kruskal's algorithm to find the cost of the minimum spanning
    # tree
    ans = kruskals(n, edges)
    print("Universe #%d:" % (case + 1), ans)