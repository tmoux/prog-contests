#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <unordered_map>
#include <unordered_set>
#include <cstring>
using namespace std;
typedef long long ll;

const int maxn = 105;
const int INF = 999999;
int n, m, A[maxn];
pair<int,int> good[maxn];
unordered_map<int,int> factors[maxn];
unordered_map<int,int> divs[maxn]; //divs[i] is list of divisors of the two numbers
unordered_map<int,vector<int>> pairsforP;
unordered_set<int> primesUsed;

void factor(int n, unordered_map<int,int>& mp) {
    if (n == 1) return;
    for (int i = 2; i*i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0) {
                n /= i;
                mp[i]++;
            }
            factor(n,mp);
            return;
        }
    }
    //must be prime
    mp[n]++;
}

struct Ngraph
{
    int weight[2*maxn][2*maxn];
    int source = 1;
    int sink = m+n+1;
    int sz = m+n+2;
    vector<int> adj[2*maxn];
    //node 0 is source, nodes 1-m are pair-nodes,
    //nodes m+1 - m+n are the array nodes, m+n+1 is the sink
    Ngraph (int p) {
        memset(weight,0,sizeof(weight));
        for (int j: pairsforP[p]) {
            int toadd = divs[j][p];
            int n1 = good[j].first+m;
            int n2 = good[j].second+m;
            weight[j][n1] = 1;
            weight[j][n2] = 1;
            weight[source][j] = 2*toadd;

            adj[source].push_back(j);
            adj[j].push_back(n1);
            adj[j].push_back(n2);
        }
        for (int j = m+1; j <= m+n; j++) {
            weight[j][sink] = INF;
            adj[j].push_back(sink);
        }
    }

    int getflow() {
        int totalflow = 0;
        vector<int> prevnode(sz), flow(sz);
        vector<bool> visited(sz);
        int maxflow, maxloc;
        while (true) {
            for (int i = source; i <= sink; i++) {
                prevnode[i] = -1;
                flow[i] = 0;
                visited[i] = false;
            }
            flow[source] = INF;

            while (true) {
                maxflow = 0;
                maxloc = -1;
                for (int i = source; i <= sink; i++) {
                    if (flow[i] > maxflow && !visited[i]) {
                        maxflow = flow[i];
                        maxloc = i;
                    }
                }

                if (maxloc == -1) break;
                if (maxloc == sink) break;

                visited[maxloc] = true;
                for (int i: adj[maxloc]) {
                    if (flow[i] < min(maxflow,weight[maxloc][i])) {
                        prevnode[i] = maxloc;
                        flow[i] = min(maxflow,weight[maxloc][i]);
                    }
                }
            }

            if (maxloc == -1) break;
            int pathcapacity = flow[sink];
            totalflow += pathcapacity;

            int curnode = sink;
            while (curnode != source) {
                int nextnode = prevnode[curnode];
                weight[nextnode][curnode] -= pathcapacity;
                weight[curnode][nextnode] += pathcapacity;
                curnode = nextnode;
            }
        }
        return totalflow;
    }
};

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> A[i];
        factor(A[i],factors[i]);
    }
    for (int i = 1; i <= m; i++) {
        int ik, jk; cin >> ik >> jk;
        good[i] = {ik,jk};
        for (auto p: factors[ik]) {
            if (factors[jk].count(p.first)) {
                divs[i][p.first] = min(p.second,factors[jk][p.first]);
                primesUsed.insert(p.first);
                pairsforP[p.first].push_back(i);
            }
        }
    }

    //make network flow graph for each prime used
    int ans = 0;
    for (int p: primesUsed) {
        Ngraph g(p);
        int flow = g.getflow();
        ans += flow;
        cout << p << ' ' << flow << '\n';
    }
    cout << ans << '\n';
    return 0;
}
	

