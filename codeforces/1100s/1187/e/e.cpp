#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n;
vector<int> adj[maxn];

int sub_size[maxn];
ll curr = 0;

void root(int i, int p) {
    sub_size[i] = 1;
    for (int j: adj[i]) {
        if (j == p) continue;
        root(j,i);
        sub_size[i] += sub_size[j];
    }
    curr += sub_size[i];
}

ll maxans = 0;
void DFS(int i, int p) {
    //cout << i << ": " << curr << '\n';
    maxans = max(maxans,curr);
    for (int j: adj[i]) {
        if (j == p) continue;
        curr += (n-2*sub_size[j]);
        DFS(j,i);
        curr -= (n-2*sub_size[j]);
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    root(1,1);
    DFS(1,1);
    cout << maxans << '\n';
}

