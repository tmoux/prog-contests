#include <bits/stdc++.h>
using namespace std;
#define oo 1000000000L

// our state is defined as <node, <time/distance, stamina>>
typedef pair<int, pair<int, int>> state;

// a struct for our edges
typedef struct Edge {
    int v, d, t;
} Edge;

// the comparator for our priority queue
struct Order {
    bool operator()(state const& a, state const& b) const {
        if(a.second.first == b.second.first)
            return a.second.second >= b.second.second;
        return a.second.first >= b.second.first;
    }
};

// here, we do a simple split-node dijstra's solution
// we split each node (platform) into different ones for each stamina level
// then we take the min of all the different ending staminas for when we reach the end
int main(void) {
    // declare numShows and read in the number of shows
    int numShows;
    scanf("%d", &numShows);
    
    for(int showI = 1; showI <= numShows; showI++) {
        int n, m, s;
        // read in the number of platforms, the number of obstacles, and the starting stamina
        scanf("%d %d %d", &n, &m, &s);
        
        // create our edge list
        vector<Edge> edges[n];
        
        for(int i = 0; i < m; i++) {
            int a, b, d, t;
            // read in the edge and make it zero based
            scanf("%d %d %d %d", &a, &b, &d, &t);
            a--;
            b--;
            
            // create our edge
            Edge e;
            e.v = b;
            e.d = d;
            e.t = t;
            
            // add this edge to our edge list
            edges[a].push_back(e);
        }
        
        // initialize all distances/times to 0
        int dists[n][s + 1];
        for(int i = 0; i < n; i++) 
            for(int j = 0; j <= s; j++)
                dists[i][j] = oo;
        
        // our starting distance for the starting node with full stamina is 0
        dists[0][s] = 0;
        
        // create our priority queue
        priority_queue<state, vector <state>, Order> pq;
        
        // add out initial state
        pq.push(make_pair(0, make_pair(0, s)));
        
        // while there are still states left
        while(!pq.empty()) {
            // pop off the top state
            state st = pq.top();
            pq.pop();
            
            // if we are not the best distance/time, just skip this one
            if(dists[st.first][st.second.second] != st.second.first)
                continue;
            
            // go through each edge from our current platform
            for(Edge e : edges[st.first]) {
                // calculate the new distance/time and the new stamina level
                int newDist = st.second.first + e.t;
                int newStam = st.second.second - e.d;
                
                // if this causes our stamina to go negative or if it doesn't improve out answer,
                // we just skip this one
                if(newStam < 0 || dists[e.v][newStam] <= newDist) continue;
                
                // store our new distance to this next platform
                dists[e.v][newStam] = newDist;
                
                // add this new state to our priority queue
                pq.push(make_pair(e.v, make_pair(newDist, newStam)));
            }
                    
        }
        
        // min all of the distances (times) for all stamina levels
        int ans = oo;
        for(int i = 0; i <= s; i++)
            if(dists[n - 1][i] < ans)
                ans = dists[n - 1][i];
        
        // print our answer
        if(ans == oo) {
            printf("Episode #%d: Wipeout!\n", showI);
        } else {
            printf("Episode #%d: %d\n", showI, ans);
        }
    }
    
    return 0;
}
