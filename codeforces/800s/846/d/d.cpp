#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct MaxQueue
{
    deque<pair<ll,int>> q;
    int cnt_added = 0;
    int cnt_removed = 0;
    ll maximum() {
        assert(!q.empty());
        return q.front().first;
    }
    void push(ll new_element) { //add new element
        while (!q.empty() && q.back().first < new_element) {
            q.pop_back();
        }
        q.push_back({new_element,cnt_added});
        cnt_added++;
    }
    void pop() {
        if (!q.empty() && q.front().second == cnt_removed) {
            q.pop_front();
        }
        cnt_removed++;
    }
};

const int maxn = 505;
int n, m, k, q;
int grid[maxn][maxn];
const int INF = 2e9+9;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m >> k >> q;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            grid[i][j] = INF;
        }
    }
    while (q--) {
        int x, y, t; cin >> x >> y >> t;
        grid[x][y] = t;
    }
    int ans = INF;
}

