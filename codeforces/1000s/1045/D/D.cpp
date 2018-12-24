#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
int N, Q;
vector<int> adj[maxn];
int parent[maxn];
double prob[maxn];

void root(int i, int p) {
    parent[i] = p;
    for (int j: adj[i]) {
        if (j == p) continue;
        root(j,i);
    }
}

double calc(int i) {
    if (parent[i] == i) return 1;
    return (1-prob[i]) * (prob[parent[i]]);        
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    for (int i = 0; i < N; i++) cin >> prob[i];
    for (int i = 0; i < N - 1; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    root(0,0);
    double ans = 0;
    for (int i = 0; i < N; i++) {
        ans += calc(i); 
        cout << i << ": " << calc(i) << '\n';
    }
    cin >> Q;
    while (Q--) {
        int i; double d;
        cin >> i >> d;
        ans -= calc(i);
        prob[i] = d;
        ans += calc(i);
        cout << ans << '\n';
    }

    return 0;
}

