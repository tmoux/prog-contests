#include <stdio.h>
#include <stdlib.h>

// Struct to hold the contents of an edge.
typedef struct edge_struct {
  int u;
  int v;
  int cost;
} Edge;

// Compares two Edges.
// Returns -1 if e1 is smaller than e2
// Returns 1 if e1 is greater than e2
// Returns 0 if e1 is equal to e2
int comp(const void * e1, const void * e2) {
  return ((Edge*)e1)->cost - ((Edge*)e2)->cost;
}

// Calculates the square distance between the two points.
int distance(int x1, int y1, int z1, int x2, int y2, int z2) {
  int dx = x1 - x2;
  int dy = y1 - y2;
  int dz = z1 - z2;
  return dx*dx + dy*dy + dz*dz;
}

// Finds the parent element for the set containing i.
int setFind(int* set, int i) {
  if(set[i] == i) {
    return i;
  }
  return set[i] = setFind(set, set[i]);
}

// Unions the the set contianing a with the set containing b.
// Returns 1 only if the two sets were unioned.
// Returns 0 if a and b were already in the same set.
int setUnion(int* set, int a, int b) {
  int pa = setFind(set, a);
  int pb = setFind(set, b);
  if(pa != pb) {
    set[pa] = pb;
    return 1;
  }
  return 0;
}

int main() {
  // Read in the number of test cases.
  int numCases;
  scanf("%d", &numCases);

  // Create all arrays with max size;
  int stars[501][3];
  int disjointSet[501];
  int maxEdges = 501 * (501-1) / 2;
  Edge edges[maxEdges];

  // Loop through each test case.
  for(int universe = 1; universe <= numCases; ++universe) {
    int numStars;
    scanf("%d", &numStars);

    // Read in the number of star systems.
    for(int curStar = 0; curStar < numStars; ++curStar) {
      scanf("%d %d %d", &stars[curStar][0], &stars[curStar][1], &stars[curStar][2]);
    }

    // Calculate the number of edges between stars.
    int size = numStars * (numStars - 1) / 2;

    // Create and save all edges.
    int ind = 0;
    for(int i = 0; i < numStars; ++i) {
      for(int j = 0; j < i; ++j) {
        edges[ind].u = i;
        edges[ind].v = j;
        edges[ind].cost = distance(stars[i][0], stars[i][1], stars[i][2],
                                   stars[j][0], stars[j][1], stars[j][2]);
        ++ind;
      }
    }

    // Sort edges with lowest cost first.
    qsort(edges, size, sizeof(Edge), comp);

    // Create a disjoint set
    for(int i = 0; i < numStars; ++i) {
      disjointSet[i] = i;
    }

    // Store the sum of the edges on the minimum spanning tree.
    int sum = 0;

    // Go through all the edges and create a minimum spanning tree.
    for(int i = 0; i < size; ++i) {
      int v1 = edges[i].v;
      int v2 = edges[i].u;

      // If two nodes are in different sets, combine the sets
      // and add the cost of the edge to the minimum spanning tree.
      if(setUnion(disjointSet, v1, v2)) {
        sum += edges[i].cost;
      }
    }

    printf("Universe #%d: %d\n", universe, sum);
  }

  return 0;
}
