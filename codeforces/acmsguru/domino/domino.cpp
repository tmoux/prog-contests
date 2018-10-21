#include <iostream>
#include <algorithm>
#include <deque>
#include <set>
using namespace std;
//It works now! This is my first (nontrivial) program I wrote using vim!
//I definitely got a lot more comfortable with the controls,
//although I still have a lot to learn. Overall, this was a pretty
//nice experience, as I managed to code all of it by myself
//I did look up someone else's code (I did not account that the graph might not
//be connected), but other than that small change, I did everything by myself
//(I realized quickly this was just a Eulerian tour).
const int maxn = 105;
int N;
pair<int,int> order[maxn]; //order[i] has pair (i, j)
struct Node
{
    int degree;
    int adj[7];
    //adj gives number of edges from the node to adj[i]
};
struct Graph
{
   int numEdges;
   Node nodes[7];
   bool keepSearch = true;
   deque<pair<int,int>> st, ansStack;
   set<int> distinctnodes;
   Graph() {
       for (int i = 0; i < 7; i++) {
           nodes[i].degree = 0;
           for (int j = 0; j < 7; j++) {
               nodes[i].adj[j] = 0;
           }
       }
   }
   void dfffs(int i, bool visited[]) {
       visited[i] = true;
       for (int j = 0; j < 7; j++) {
           if (nodes[i].adj[j] > 0 && !visited[j]) {
               dfffs(j,visited);
           }
       }
   }
   bool isConnected() {
       bool visited[7];
       for (int i = 0; i < 7; i++) {
           visited[i] = false;
       }
       for (int i = 0; i < 7; i++) {
           if (nodes[i].degree > 0) {
               dfffs(i,visited);
               break;
           }
       }
       int total = 0;
       for (int i = 0; i < 7; i++) {
           total += visited[i];
       }
       return total == distinctnodes.size();
   }
   int countOddNodes() {
       int res = 0;
       for (int i = 0; i < 7; i++) {
           if (nodes[i].degree % 2 == 1) {
               res++;
           }
       }
       return res;
   }
   int getStartNode() {
       int numOdd = countOddNodes();
       for (int i = 0; i < 7; i++) {
           if (numOdd > 0 && nodes[i].degree % 2 == 1) {
               return i;
           }
           else if (numOdd == 0 && nodes[i].degree > 0) {
               return i;
           }
       }
   }

   void dfs(int i, int reachEdges) {
      if (reachEdges == N) {
          keepSearch = false;
          for (auto a: st) {
              ansStack.push_back(a);
          }
      }
      if (keepSearch) {
          for (int j = 0; j < 7; j++) {
              if (nodes[i].adj[j] > 0) {
                  nodes[i].adj[j]--;
                  nodes[j].adj[i]--;
                  st.push_back({i,j});
                  dfs(j,reachEdges+1);
                  st.pop_back();
                  nodes[i].adj[j]++;
                  nodes[j].adj[i]++;
             }
          }
    
      }
         }
};

pair<int,char> getDomino(int curr, int nxt) {
    for (int i = 1; i <= N; i++) {
        if (order[i].first == curr && order[i].second == nxt) {
            order[i] = {-1,-1};
            return {i,'+'};
        }
        if (order[i].second == curr && order[i].first == nxt) {
            order[i] = {-1,-1};
            return {i,'-'};
        }
    }
};

int main()
{
    //freopen("input.in","r",stdin);
    cin >> N;
    Graph g;
    g.numEdges = N;
    for (int i = 1; i <= N; i++) {
        int a, b; cin >> a >> b;
        order[i] = {a,b};
        g.nodes[a].adj[b]++;
        g.nodes[b].adj[a]++;
        g.nodes[a].degree++;
        g.nodes[b].degree++;
        g.distinctnodes.insert(a);
        g.distinctnodes.insert(b);
    }
    int numOdd = g.countOddNodes(); 
    int curr = g.getStartNode();
    if (!g.isConnected() || numOdd > 2) {
        cout << "No solution\n";
        return 0;
    }
    
    //now we know it is possible
    //int curr = startNode;
    int nxt;
    g.dfs(curr,0);
    for (auto p: g.ansStack) {
        auto res = getDomino(p.first,p.second);
        cout << res.first << ' ' << res.second << '\n';
    }
}
