#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
#define trav(a,x) for (auto& a : x)
#define uid(a, b) uniform_int_distribution<int>(a, b)(rng)
 
#define sz(x) (int)(x).size()
#define mp make_pair
#define pb push_back
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define ins insert

typedef vector<ll> vl;
typedef vector<int> vi;

const int maxn = 51;
const int M = 1e9+7;
int N;
ll K;

vector<vl> matMul(vector<vl>& A, vector<vl> &B) {
    int R = sz(A), C = sz(B[0]), I = sz(B);
    vector<vl> res(R, vl(C, 0));
    F0R(i, R) {
        F0R(j, I) {
            F0R(k, C) {
                res[i][k] += (A[i][j] * B[j][k]) % M;
                res[i][k] %= M;
            }
        }
    }
    return res;
}

vector<vl> exp(vector<vl> M, ll P) {
    vector<vl> R(sz(M), vl(sz(M[0]), 0));
    F0R(i, sz(M)) {
        R[i][i] = 1;
    }
    for (; P; P /= 2, M = matMul(M, M)) if (P & 1) R = matMul(R, M);
    return R;
}

//from https://cp-algorithms.com/graph/dinic.html
//Complexity: O(E*V^2)
struct FlowEdge {
   int v, u;
   long long cap, flow = 0;
   FlowEdge(int v, int u, long long cap) : v(v), u(u), cap(cap) {}
};

struct Dinic {
   const long long flow_inf = 1e18;
   vector<FlowEdge> edges;
   vector<vector<int>> adj;
   int n, m = 0;
   int s, t;
   vector<int> level, ptr;
   queue<int> q;

   Dinic(int n, int s, int t) : n(n), s(s), t(t) {
       adj.resize(n);
       level.resize(n);
       ptr.resize(n);
   }

   void add_edge(int v, int u, long long cap) {
       edges.emplace_back(v, u, cap);
       edges.emplace_back(u, v, 0);
       adj[v].push_back(m);
       adj[u].push_back(m + 1);
       m += 2;
   }

   bool bfs() {
       while (!q.empty()) {
           int v = q.front();
           q.pop();
           for (int id : adj[v]) {
               if (edges[id].cap - edges[id].flow < 1)
                   continue;
               if (level[edges[id].u] != -1)
                   continue;
               level[edges[id].u] = level[v] + 1;
               q.push(edges[id].u);
           }
       }
       return level[t] != -1;
   }

   long long dfs(int v, long long pushed) {
       if (pushed == 0)
           return 0;
       if (v == t)
           return pushed;
       for (int& cid = ptr[v]; cid < (int)adj[v].size(); cid++) {
           int id = adj[v][cid];
           int u = edges[id].u;
           if (level[v] + 1 != level[u] || edges[id].cap - edges[id].flow < 1)
               continue;
           long long tr = dfs(u, min(pushed, edges[id].cap - edges[id].flow));
           if (tr == 0)
               continue;
           edges[id].flow += tr;
           edges[id ^ 1].flow -= tr;
           return tr;
       }
       return 0;
   }

   long long flow() {
       long long f = 0;
       while (true) {
           fill(level.begin(), level.end(), -1);
           level[s] = 0;
           q.push(s);
           if (!bfs())
               break;
           fill(ptr.begin(), ptr.end(), 0);
           while (long long pushed = dfs(s, flow_inf)) {
               f += pushed;
           }
       }
       return f;
   }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> K;
    vector<vl> aa(N, vl(N, 0));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> aa[i][j];
        }
    }
    auto ans = exp(aa,K);
    int tot = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            tot = (tot + ans[i][j]) % M;
        }
    }
    cout << tot << '\n';


    return 0;
}

