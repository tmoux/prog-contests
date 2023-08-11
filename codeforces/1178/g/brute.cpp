#include <bits/stdc++.h>
using namespace std;
using ll = long long;
typedef long double ld;

const int maxn = 2e5+5;
const int BLK = 300;
int n, q;

int tin[maxn], tout[maxn];
ll a[maxn], b[maxn];
vector<int> adj[maxn];
int t = 0;

void DFS(int i) {
    tin[i] = t++;
    for (int j: adj[i]) {
        DFS(j);
    }
    tout[i] = t-1;
}

void ADD(int l, int r, int x) {
    for (; l <= r; l++) {
        a[l] += x;
    }
}

ll QUERY(int l, int r) {
    ll res = 0;
    for (; l <= r; l++) {
        res = max(res,abs(a[l]*b[l]));
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> q;
    for (int i = 2; i <= n; i++) {
        int pi; cin >> pi;
        adj[pi].push_back(i);
    }
    DFS(1); 
    for (int i = 1; i <= n; i++) {
        int ai; cin >> ai;
        a[tin[i]] += ai;
        a[tout[i]+1] -= ai;
    }
    for (int i = 1; i <= n; i++) {
        int bi; cin >> bi;
        b[tin[i]] += bi;
        b[tout[i]+1] -= bi;
    }
    for (int i = 1; i <= n; i++) {
        a[i] += a[i-1];
        b[i] += b[i-1];
    }
    for (int i = 0; i < n; i++) {
        //printf("%d: a = %d, b = %d\n",i,a[i],b[i]);
        b[i] = abs(b[i]);
    }

    while (q--) {
        int t, v; cin >> t >> v;
        if (t == 1) {
            int x; cin >> x;
            ADD(tin[v],tout[v],x);
        }
        else {
            cout << QUERY(tin[v],tout[v]) << '\n';
        }
    }
}

