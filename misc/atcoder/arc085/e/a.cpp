#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 105;
const ll INF = 1LL<<55;
int n; 

ll a[maxn];
vector<int> adj[maxn];

struct FF
{
    ll cap[maxn][maxn];
    bool visited[maxn], seen[maxn];
    ll source, sink;
    FF() {
        source = 0;
        sink = n + 1;
        //fill with zeros
        memset(cap,0,sizeof(cap));
        memset(visited,false,sizeof(visited));
        //add edges
        for (int i = 1; i <= n; i++) {
            if (a[i] <= 0) {
                cap[source][i] = -a[i];                    
            }
            else {
                cap[i][sink] = a[i];
            }
            for (int j: adj[i]) {
                cap[i][j] = INF;
            }
        }

        /*
        cout << '\n';
        for (ll i = 0; i <= sink; i++) {
            for (ll j = 0; j <= sink; j++) {
                cout << cap[i][j] << ' ';
            }
            cout << '\n';
        }
        */
    }

    ll dfs(ll i, ll bneck) {
        if (i == sink) {
            return bneck;
        }
        if (visited[i]) return 0;
        visited[i] = true;
        for (int j = 0; j <= sink; j++) {
            if (cap[i][j] > 0) {
                ll f = dfs(j,min(bneck,cap[i][j]));
                if (f > 0) {
                    //update, recurse upwards
                    cap[i][j] -= f;
                    cap[j][i] += f;
                    return f;
                }
            }
        }
        return 0;
    }

    ll getflow() {
        ll flow = 0;
        while (true) {
            memset(visited,false,sizeof(visited));
            ll f = dfs(source,INF);
            if (f == 0) break;
            flow += f;
        }
        return flow;
    }

    void findReachable(int i) {
        seen[i] = true;
        for (int j = 0; j <= sink; j++) {
            if (!seen[j] && cap[i][j] > 0) {
                findReachable(j);
            }
        }
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    ll sum = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (a[i] > 0) sum += a[i];
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 2*i; j <= n; j += i) {
            adj[i].push_back(j);
            //adj[j].push_back(i);
        }
    }
    FF graph = FF();
    ll flow = graph.getflow();
    /*
    graph.findReachable(graph.source);
    ll r = 0;
    for (int i = 1; i <= n; i++) {
        if (graph.seen[i]) {
            r += a[i];
            //cout << i << ' ' << a[i] << '\n';
        }
    }
    cout << r << '\n';
    */
    //flow = min(0LL,flow);
    //cout << flow << '\n';
    cout << (sum-flow) << '\n';
}

