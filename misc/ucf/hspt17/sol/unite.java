import java.util.*;

public class unite {
    
    // the number of star systems in our current universe
    static int n;
    
    // the locations of the star systems
    static int[] xs, ys, zs;
    
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        
        // read in the number of test cases
        int t = in.nextInt();
        
        for(int universeNumber = 1; universeNumber <= t; universeNumber++) {
            // read in the number of star systems
            n = in.nextInt();
            
            // initialize the xs, ys, and zs arrays
            xs = new int[n];
            ys = new int[n];
            zs = new int[n];
            
            // read in the locations of all the star systems
            for(int i = 0; i < n; i++) {
                xs[i] = in.nextInt();
                ys[i] = in.nextInt();
                zs[i] = in.nextInt();
            }
            
            // create an arraylist of all our edges
            ArrayList<Edge> edges = new ArrayList<>();
            
            // add each edge to the arraylist
            // because when we add a teleporter from i to j we also have the
            // reverse teleporter, we only need one edge for each pair of star systems
            for(int i = 0; i < n; i++) {
                for(int j = i + 1; j < n; j++) {
                    // create the edge
                    Edge edge = new Edge(i, j);
                    
                    // add this edge to our list
                    edges.add(edge);
                }
            }
            
            // create a disjoint set for our n star systems
            DisjointSet dset = new DisjointSet(n);
            
            // sort all of our edges
            Collections.sort(edges);
            
            // initialize our totalCost to 0
            int totalCost = 0;
            
            // loop through each edge we may consider adding
            // 
            // every edge we add will either take two sets of star systems which are
            // not connected and connect them or it will connect two star systems
            // which are already connected. However, we don't then need this redundant
            // edge so we only consider edges that connect disjoint star systems.
            // 
            // we ultimately want to connect all n star systems together
            // thus, we will need to use (n - 1) edges to do this
            // 
            // we can geedily always use the smallest edge which is available and this
            // will give us the optimal answer because any future edges will always have
            // the same cost or more 
            // 
            // our runtime is O(n^2 log n + n log n) because we have to sort our edges
            // and for each of our n^2 edges we have to union the two vertices which
            // we are considering connecting. Only (n - 1) of these unions will be joining
            // disjoint star systems thus the disjointSet adds the (n log n) part of our runtime
            // 
            // this simplifies to give us a runtime of O(n^2 log n)
            for(Edge edge : edges) {
                // try connecting the two star systems that this edge is between
                if(dset.union(edge.a, edge.b)) {
                    // if the union function returned true, we know that a and b
                    // were initially separate, thus we needed to use this edge
                    
                    // because we used this edge, we increment our total cost by the edges' cost
                    totalCost += edge.cost;
                }
            }
            
            // print our answer
            System.out.printf("Universe #%d: %d\n", universeNumber, totalCost);
        }
    }
    
    // this class starts off with a collection of n sets that are all disjoint
    // Ex: { {0}, {1}, {2}, ... , {n - 2}, {n - 1} }
    // 
    // each node has a parent
    // all nodes that share a parent(or are that parent themselves) are in the same set
    // thus, each node starts off as it's own parent
    // 
    // node:    0  |  1  |  2  |  3
    // parent:  0  |  1  |  2  |  3
    // sets:   { {0}, {1}, {2}, {3} }
    // 
    // to join two sets, we set the parent of the root of one set to be the other set's parent
    // if we join 1 and 2, we get:
    // node:    0  |  1  |  2  |  3
    // parent:  0  |  2  |  2  |  3
    // sets:   { {0}, {1, 2}, {3} }
    // 
    // now, if we union 3 with 1, we get
    // node:    0  |  1  |  2  |  3
    // parent:  0  |  2  |  2  |  1
    // sets:   { {0}, {1, 2, 3} }
    // 
    // here, we see that when searching for a parent, we need to go all the way up
    // to the top of the tree. That is, we keep going up until we find someone that is
    // their own parent. Anyone that is their own parent is the root of their tree
    // 
    // thus, to check if two nodes are in the same set, we find both of their parents
    // and then check if their parents are the same. If so, we know that they are in the same set
    // 
    // 
    // sometimes, when searching for the root of our set's tree, we may have to go up
    // a very long chain. Ex: 5 -> 4 -> 2 -> 1 -> 3
    // 
    // this is not too big of a deal, however if we try to find 5's parent many times, this will
    // cause our disjoint set to run pretty slow
    // 
    // thus, after we discover that 5's parent up the chain is 3, we simply store that
    // and set 5's parent to simply be 3. Because we are doing this recursively,
    // the entire chain gets compressed:
    // 
    //      4
    //      |
    //      v
    // 5 -> 3 <- 2
    //      ^
    //      |
    //      1
    //      
    // now, we can find the parent's really quickly
    // 
    // this gives our disjoint set a worst case runtime of O(n log n)
    // we can speed this up by doing smart things when merging but this is not
    // needed for this problem.
    static class DisjointSet {
        // an array that stores whom each star system's parent is
        int[] parents;
        
        // create a disjoint set of size n
        public DisjointSet(int n) {
            // initialize our parents array
            parents = new int[n];
            
            // everyone starts out as their own parent
            for(int i = 0; i < n; i++)
                parents[i] = i;
        }
        
        // returns our parent all the way up the tree
        // we also set our parent to the parent we find
        // this speeds up future calls to the getParent function
        public int getParent(int a) {
            // if we are our own parent, we return ourself
            if(parents[a] == a) return a;
            
            // find the parent of our parent
            int par = getParent(parents[a]);
            
            // set our parent to now be the parent we find
            parents[a] = par;
            
            // return the parent we found
            return par;
        }
        
        // this function unions the set containing a with the set containing b
        // if a and b are already together (their parents are the same),
        // we return false
        // otherwise, we return true meaning we successfully unioned a and b
        public boolean union(int a, int b) {
            // find the parents of both a and b
            int pa = getParent(a);
            int pb = getParent(b);
            
            // if their parents are the same, they are already in the same set
            // thus, we return false
            if(pa == pb)
                return false;
            
            // now, we set a's parent to be b
            // this will essentially union the set containing a with the set containing b
            parents[pa] = pb;
            
            // return true because we successfully unioned a and b
            return true;
        }
    }
    
    static class Edge implements Comparable<Edge> {
        // the two star systems this edge connects and the cost to travel between them
        int a, b, cost;
        
        public Edge(int aa, int bb) {
            a = aa;
            b = bb;
            
            // calculate the squared distance between a and b
            int dx = xs[a] - xs[b];
            int dy = ys[a] - ys[b];
            int dz = zs[a] - zs[b];
            
            int distSquared = dx * dx + dy * dy + dz * dz;
            
            // our cost is equal to the squared distance
            cost = distSquared;
        }
        
        // compare edges so the one with the smaller cost comes first
        public int compareTo(Edge e) {
            return Integer.compare(cost, e.cost);
        }
    }
    
}
