#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, v[maxn];
vector<int> adj[maxn];

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int p, vi; cin >> p >> vi;
        if (p != 0) adj[p].push_back(i);
        v[i] = vi;
    }
    
}

