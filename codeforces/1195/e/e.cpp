#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 3005;
int n, m, a, b;
int g_0, x, y, z;
int g[maxn*maxn];

struct MinQueue
{
    deque<pair<int,int>> q;
    int cnt_added = 0;
    int cnt_removed = 0;
    int minimum() {
        assert(!q.empty());
        return q.front().first;
    }
    void push(int new_element) { //add new element
        while (!q.empty() && q.back().first > new_element) {
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

MinQueue mq[maxn], cols[maxn];

int grid[maxn][maxn];
vector<pair<int,int>> pos[maxn*maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m >> a >> b;
    cin >> g_0 >> x >> y >> z;
    g[0] = g_0;
    set<int> used;
    for (int i = 1; i <= n*m; i++) {
        g[i] = ((1LL*g[i-1]*x + y)) % z;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            grid[i][j] = g[i*m+j];
        }
    }
    ll sum = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < b; j++) {
            mq[i].push(grid[i][j]);
        }
    }
    for (int j = b-1; j < m; j++) {
        for (int i = 0; i < a; i++) {
            cols[j].push(mq[i].minimum());
        }
        for (int i = a-1; i < n; i++) {
            sum += cols[j].minimum();
            
            if (i + 1 < n) {
                cols[j].pop();
                cols[j].push(mq[i+1].minimum());
            }
        }

        if (j+1 < m) {
            for (int i = 0; i < n; i++) {
                mq[i].pop();
                mq[i].push(grid[i][j+1]);
            }
        }
    }
    cout << sum << '\n';
}
