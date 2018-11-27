import java.util.*;
// Author: Derek Goodwin

public class wipeout{
	static int oo = Integer.MAX_VALUE;
	
	static class Node{
		
		int dex; // only purpose: tell whether we're on the end platform
		int timeToGetHere = oo; // for the topsort
		int amtBackEdges = 0; // for the topsort
		boolean visited = false; // for the BFS
		
		ArrayList<Edge> nexts = new ArrayList<>(1);
		
		Node(int dexx){
			dex = dexx;
		}
		
		// be careful; this function also modifies the nexts arraylist of this
		void connect(Node that, int timee){
			Edge e = new Edge(this, that, timee);
			this.nexts.add(e);
		}
	}
	static class Edge{
		
		// technically the 'a' pointer is unnecessary, but still useful for
		// debugging purposes
		Node a, b; // a is start, b is end
		
		int timeToCross;
		
		// directed from A to B
		Edge(Node aa, Node bb, int timee){
			a = aa; b = bb; timeToCross = timee;
		}
	}
	public static void main(String[] args){
		
		Scanner in = new Scanner(System.in);
		int T = in.nextInt();
		
		for(int t = 1; t <= T; t++){
			
			// first line of input for a test case
			int N = in.nextInt(), M = in.nextInt(), S = in.nextInt();
			
			// each platform uses S+1 nodes for S+1 different levels of stamina
			Node[][] nodes = new Node[N][S+1];
			for(int n = 0; n < N; n++){
				for(int s = 0; s <= S; s++){
					// it will be useful to us that (S+1) nodes all have the
					// same index later
					nodes[n][s] = new Node(n);
				}
			}
			
			// for each edge...
			for(int m = 0; m < M; m++){
				
				// edge input
				int A = in.nextInt() - 1, B = in.nextInt() - 1;
				int D = in.nextInt(), TIME = in.nextInt();
				
				// make all valid connections
				for(int s = S; s - D >= 0; s--){
					nodes[A][s].connect(nodes[B][s - D], TIME);
				}
			}
			
			// because every node has positive stamina cost, we can model the
			// problem as shortest path in a directed acyclic graph. this can
			// be done in O(N + M) with a topological sort, but only after
			// we've counted the amount of incoming edges from every node we
			// can actually reach.
			// this BFS counts that amount for each edge.
			ArrayDeque<Node> queue = new ArrayDeque<>();
			queue.offer(nodes[0][S]);
			nodes[0][S].visited = true;
			
			while(!queue.isEmpty()){
				Node pop = queue.pop();
				
				for(Edge e : pop.nexts){
					
					// the next edge has one new reachable back edge
					e.b.amtBackEdges++;
					
					if(!e.b.visited){
						e.b.visited = true;
						queue.offer(e.b);
					}
				}
			}
			
			// now we topsort through the graph to find the shortest path to
			// the finish.
			queue.offer(nodes[0][S]);
			nodes[0][S].timeToGetHere = 0;
			int minTime = oo;
			
			while(!queue.isEmpty()){
				
				Node pop = queue.pop();
				
				// if this is the finish, record the time taken to get here
				if(pop.dex == N-1 && minTime > pop.timeToGetHere){
					minTime = pop.timeToGetHere;
				}
				
				for(Edge e : pop.nexts){
					// edge reach recorded
					e.b.amtBackEdges--;
					// minimum travel time updated
					if(e.b.timeToGetHere > pop.timeToGetHere + e.timeToCross){
						e.b.timeToGetHere = pop.timeToGetHere + e.timeToCross;
					}
					// only put e.b in the queue if no more incoming edges to
					// it
					if(e.b.amtBackEdges == 0){
						queue.offer(e.b);
					}
				}
			}
			
			System.out.print("Episode #" + t + ": ");
			if(minTime == oo){
				System.out.println("Wipeout!");
			}
			else{
				System.out.println(minTime);
			}
		}
	}
}
