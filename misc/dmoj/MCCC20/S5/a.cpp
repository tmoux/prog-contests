#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 505;
int N, K;
vector<int> adj[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> K;
    for (int i = 0; i < N-1; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

}
