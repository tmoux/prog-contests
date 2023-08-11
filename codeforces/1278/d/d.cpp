#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 5e5+5;
int n;
int a[2*maxn];

int bit[2*maxn];
void add(int i, int x) {
    for (; i <= 2*n; i += i & (-i))
        bit[i] += x;
}

int sum(int i) {
    int r = 0;
    for (; i; i -= i & (-i)) {
        r += bit[i];
    }
    return r;
}

vector<int> adj[maxn];

bool vis[maxn];
void dfs(int i) {
    vis[i] = true;
    for (int j: adj[i]) {
        if (vis[j]) continue;
        dfs(j);
    }
}

pair<int,int> p[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int l, r; cin >> l >> r;
        a[l] = i;
        a[r] = -i;
        p[i] = {l,r};
    }
    ll deg = 0;
    for (int i = 1; i <= 2*n; i++) {
        if (a[i] > 0) {
            deg += sum(p[a[i]].second);
            add(p[a[i]].second,1);
        }
        else add(p[-a[i]].second,-1);
    }
    //cout << deg << endl;
    if (deg != n-1) {
        cout << "NO\n";
        return 0;
    }
    set<pair<int,int>> curr; //r-pos, i
    for (int i = 1; i <= 2*n; i++) {
        if (a[i] > 0) {
            for (auto q: curr) {
                int rpos = q.first;
                int idx = q.second;
                if (rpos > p[a[i]].second) break;
                adj[a[i]].push_back(idx);
                adj[idx].push_back(a[i]);
            }
            curr.insert({p[a[i]].second,a[i]});
        }
        else {
            curr.erase({p[-a[i]].second,-a[i]});
        }
    }
    dfs(1);
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            cout << "NO\n";
            return 0;
        }
    }
    cout << "YES\n";
}

