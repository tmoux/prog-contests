#include <bits/stdc++.h>
#define mp make_pair
#define all(x) begin(x),end(x)
using namespace std;
using ll = long long;
using vi = vector<int>;

const int maxn = 31;
int n, m, a[maxn];
set<vi> parts, nparts;
set<pair<vi,int>> seen;

void dfs(vi x, vi l, int s, int pos = 0) {
    sort(all(l));
    if (seen.count(mp(l,s))) return;
    seen.insert(mp(l,s));
    if (pos == x.size()) {
        nparts.insert(l);
        return;
    }
    for (int i = 0; i <= s && i <= x[pos]/2; i++) {
        if (i) l.push_back(i);
        if (i!=x[pos]) l.push_back(x[pos]-i);
        dfs(x,l,s-i,pos+1);
        if (i!=x[pos]) l.pop_back();
        if (i) l.pop_back();
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    parts.insert({n});
    for (int i = 0; i < m; i++) {
        cin >> a[i];
        a[i] = min(a[i],n-a[i]); 
        vector<int> l;
        for (auto& v: parts) {
            seen.clear();
            dfs(v,l,1<<a[i]);
        }
        parts = nparts;
        nparts.clear();
        int mx = 0;
        for (auto& v: parts) {
            int cnt = 0;
            for (auto& j: v) if (j == 1) cnt++;
            mx = max(mx,cnt);
            if (mx == n) {
                cout << n << '\n';
                return 0;
            }
        }
        if (i==m-1) {
            cout << mx << '\n';
        }
    }
}
