#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2005, M = 1e9+7;
int N;
vector<int> adj[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    for (int i = 0; i < n-1; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

}
