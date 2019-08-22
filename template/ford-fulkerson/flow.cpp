const ll INF = 1LL<<60;

struct FF
{
    ll cap[maxn][maxn];
    bool visited[maxn];
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
};
