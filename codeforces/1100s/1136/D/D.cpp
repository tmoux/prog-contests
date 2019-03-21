#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 3e5+5;
int n, m;
int pos[maxn];
int a[maxn];
vector<int> swaps[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int pi; cin >> pi;
        pos[pi] = i;
        a[i] = pi;
    }
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        if (pos[a] < pos[b]) swaps[a].push_back(b);
    }
    set<int> ahead;
    ahead.insert(a[n]);
    for (int i = n - 1; i >= 1; i--) {
        int s = a[i];
        int cnt = 0;
        sort(swaps[s].begin(),swaps[s].end());
        swaps[s].erase(unique(swaps[s].begin(),swaps[s].end()),swaps[s].end());
        for (int j: swaps[s]) {
            if (ahead.count(j)) {
                cnt++;
            }
        }
        if (cnt == ahead.size()) {}
        else ahead.insert(s);
    }
    cout << (n-ahead.size()) << '\n';
}

