#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 5e4+5;
int N, M, K;
struct Edge
{
    int to, weight;
};
vector<Edge> adj[maxn];
int food[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> M >> K;
    for (int i = 0; i < M; i++) {
        int a, b, t; cin >> a >> b >> t;
        adj[a].push_back({b,t});
        adj[b].push_back({a,t});
    }
    for (int i = 0; i < K; i++) {
        int a, b; cin >> a >> b;
        food[a] = max(food[a],b);
    }
    

    return 0;
}

