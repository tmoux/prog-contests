#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 5e4+5;
const int INF = 2e9+9;
int N, M, K;
typedef pair<int,int> Edge;
vector<Edge> adj[maxn];
int food[maxn];
bool poss[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    freopen("dining.in","r",stdin); freopen("dining.out","w",stdout);
    cin >> N >> M >> K;
    for (int i = 0; i < M; i++) {
        int a, b, t; cin >> a >> b >> t;
        adj[a].push_back({b,t});
        adj[b].push_back({a,t});
    }
    for (int i = 0; i < K; i++) {
        int a, f; cin >> a >> f;
        food[a] = max(food[a],f);
    }
    priority_queue<Edge, vector<Edge>, greater<Edge>> pq;
    vector<int> dist(N+1,INF);
    pq.push({0,N});
    dist[N] = 0;
    while (!pq.empty()) {
        int u = pq.top().second; pq.pop();
        for (Edge e: adj[u]) {
            int v = e.first;
            int weight = e.second;
            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v],v});
            }
        }
    }

    vector<int> d2(N+1,INF);
    for (int i = 1; i <= N; i++) {
        if (food[i] > 0) {
            pq.push({dist[i]-food[i],i});
            d2[i] = dist[i]-food[i];
            poss[i] = true;
        }
    }
    while (!pq.empty()) {
        int u = pq.top().second;
        int w = pq.top().first;
        pq.pop();
        for (Edge e: adj[u]) {
            int v = e.first;
            int weight = e.second;
            if (w + weight <= dist[v]) poss[v] = true;
            if (d2[v] > d2[u] + weight) {
                d2[v] = d2[u] + weight;
                pq.push({d2[v],v});
            }
        }
    }
    //output
    for (int i = 1; i < N; i++) {
        cout << poss[i] << '\n';
    }



    return 0;
}
