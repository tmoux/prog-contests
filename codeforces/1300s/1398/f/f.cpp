#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e6+6;
const int INF = 2e9;
int n;
string s;
int ans[maxn];
vector<int> pos[2];
vector<pair<int,int>> space[2];
set<int> avail[2];

int get_next(int idx, int j, int x) {
    auto it = lower_bound(pos[j].begin(),pos[j].end(),idx);
    if (it != pos[j].end() && *it - idx >= x) {
        return idx + x;
    }
    else {
        auto it = avail[j].lower_bound(idx);
        if (it != avail[j].end()) {
            return *it + x + 1;
        }
        else {
            return INF;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> s;
    for (int i = 0; i < n; i++) {
        if (s[i] == '0') pos[0].push_back(i);
        else if (s[i] == '1') pos[1].push_back(i);
    }
    pos[0].push_back(n);
    pos[1].push_back(n);
    for (int j = 0; j <= 1; j++) {
        for (int i = 0; i+1 < pos[j].size(); i++) {
            space[j].push_back({pos[j][i+1]-pos[j][i]-1,pos[j][i]});
            avail[j].insert(pos[j][i]);
        }
        sort(space[j].begin(),space[j].end(),greater<pair<int,int>>());
    }
    ans[1] = n;
    for (int x = 2; x <= n; x++) {
        for (int j = 0; j <= 1; j++) {
            while (!space[j].empty() && space[j].back().first < x) {
                avail[j].erase(space[j].back().second);
                space[j].pop_back();
            }
        }
        int idx = 0;
        int curans = 0;
        while (true) {
            int nxt = min(get_next(idx,0,x),get_next(idx,1,x));
            if (nxt == INF) break;
            else {
                idx = nxt;
                curans++;
            }
        }
        ans[x] = curans;
    }
    for (int x = 1; x <= n; x++) {
        cout << ans[x] << ' ';
    }
    cout << '\n';
}
