#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n;
vector<int> adj[maxn];
int k;

bool can_pair(vector<int>& v, int skip) {
    for (int l = 0, r = (int)v.size()-1; l < r; l++,r--) {
        if (l == skip) l++;
        if (r == skip) r--;
        if (l >= r) break;
        if (v[l] + v[r] < k) return false;
    }
    return true;
}

int dfs(int i, int p) {
    vector<int> v;
    for (int j: adj[i]) {
        if (j == p) continue;
        int aj = dfs(j,i);
        if (aj == -1) return -1;
        v.push_back(aj+1);
    }
    int ret = -1;
    auto vv = v; if (vv.size()&1) vv.push_back(0);
    sort(vv.begin(),vv.end());
    if (can_pair(vv,-1)) ret = 0;
    if (i == p) return ret;

    vv = v; if (!(vv.size()&1)) vv.push_back(0);
    sort(vv.begin(),vv.end());
    int lo = -1, hi = vv.size();
    while (lo + 1 < hi) {
        int mid = (lo+hi)/2;
        if (can_pair(vv,mid)) {
            lo = mid;
        }
        else hi = mid;
    }
    if (lo >= 0) ret = vv[lo];
    return ret;
}

int main()
{
    freopen("deleg.in","r",stdin); freopen("deleg.out","w",stdout);
    cin >> n;
    for (int i = 0; i < n-1; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    int lo = 1, hi = n;
    while (lo + 1 < hi) {
        int mid = (lo+hi)/2;
        k = mid;
        int tr = dfs(1,1);
        if (tr != -1) {
            lo = mid;
        }
        else {
            hi = mid;
        }
    }
    cout << lo << '\n';
}
