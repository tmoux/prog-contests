#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 2e5+5, INF = 1e9;
int n, c[maxn], a[maxn];
bool vis[maxn], onStack[maxn];
vector<vector<int>> paths;
vector<int> curr;

bool stop = false;
int markCycle(int i) {
    if (vis[i]) return 0;
    if (onStack[a[i]]) {
        curr.push_back(i);
        return a[i];
    }
    onStack[i] = true;
    int r = markCycle(a[i]);
    if (r == 0) return 0;
    if (r == i) {
        stop = true;     
        curr.push_back(i);
        paths.push_back(curr);
        curr.clear();
    }
    if (!stop) {
        curr.push_back(i);
    }
    onStack[i] = false;
    vis[i] = true;
    return r;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> c[i];
    for (int i = 1; i <= n; i++) {
        int ai; cin >> ai;
        a[i] = ai;
    }
    for (int i = 1; i <= n; i++) {
        stop = false;
        markCycle(i);
    }

    ll res = 0;
    for (vector<int> v: paths) {
        int r = INF;
        for (int i: v) {
            r = min(r,c[i]);
        }
        res += r;
    }
    cout << res << '\n';

    return 0;
}
	

