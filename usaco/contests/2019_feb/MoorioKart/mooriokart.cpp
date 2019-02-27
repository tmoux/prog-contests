#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1505;
int N, M, X, Y;
struct Edge
{
    int to, w;
};
vector<Edge> adj[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    freopen("mooriokart.in","r",stdin); freopen("mooriokart.out","w",stdout);
    cin >> N >> M >> X >> Y;
    int last = -1;
    for (int i = 0; i < M; i++) {
        int a, b, d; cin >> a >> b >> d;
        adj[a].push_back({b,d});
        adj[b].push_back({a,d});
        last = d;
    }
    cout << (N*Y-last) << "\n";

    return 0;
}

