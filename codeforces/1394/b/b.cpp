#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5, maxk = 10;
int n, m, k;
vector<pair<int,int>> in[maxn], out[maxn];

bool edge[maxk][maxk][maxk][maxk];

vector<int> vec = {0};
int ans = 0;
void recurse(int i) {
    if (i > k) {
        /*
        for (auto j = 1; j <= k; j++) {
            cout << vec[j] << ' ';
        }
        */
        bool poss = true;
        for (int u = 1; u <= k; u++) {
            for (int v = 1; v <= k; v++) {
                if (edge[u][vec[u]][v][vec[v]]) {
                    poss = false;
                    break;
                }
            }
        }
        if (poss) ans++;
        /*
        cout << ": " << poss;
        cout << '\n';
        */
        return;
    }
    for (int j = 1; j <= i; j++) {
        vec.push_back(j);
        recurse(i+1);
        vec.pop_back();
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m >> k;
    for (int i = 0; i < m; i++) {
        int u, v, w; cin >> u >> v >> w;
        out[u].push_back({w,v});
        in[v].push_back({w,u});
    }
    for (int i = 1; i <= n; i++) {
        sort(out[i].begin(),out[i].end());
    }
    for (int i = 1; i <= n; i++) {
        map<pair<int,int>,int> mp;
        for (auto p: in[i]) {
            int u = p.second;
            int wt = p.first;
            int c = distance(out[u].begin(),lower_bound(out[u].begin(),out[u].end(),make_pair(wt,i))) + 1;
            mp[make_pair(out[u].size(),c)]++;
            //cout << u << ' ' << i << ": " << c << endl;
        }
        for (auto i: mp) {
            for (auto j: mp) {
                if (i.first == j.first && i.second == 1) continue;
                edge[i.first.first][i.first.second][j.first.first][j.first.second] = 1;
            }
        }
    }
    recurse(1);
    cout << ans << '\n';
}
