#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 7005;
int skill[maxn];
ll algo[maxn];

vector<int> dir[maxn];

bool used[maxn];
int n;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    map<ll,vector<int>> cnt;
    for (int i = 0; i < n; i++) {
        cin >> algo[i];
        cnt[algo[i]].push_back(i);
    }
    for (int i = 0; i < n; i++) {
        cin >> skill[i];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            if ((algo[i] | algo[j]) == algo[i]) {
                //i is parent of j
                dir[i].push_back(j);
            }
        }
    }
    queue<int> q;
    for (auto p: cnt) {
        if (p.second.size() >= 2) {
            for (int i: p.second) {
                q.push(i);
                used[i] = true;
            }
        }
    }
    while (!q.empty()) {
        int f = q.front(); q.pop();
        for (int j: dir[f]) {
            if (used[j]) continue;
            q.push(j);
            used[j] = true;
        }
    }

    ll ans = 0;
    for (int i = 0; i < n; i++) {
        if (used[i]) ans += skill[i];
    }
    cout << ans << '\n';
}
