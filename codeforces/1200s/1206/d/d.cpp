#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n;
ll a[maxn];
int cnt[100];

vector<int> adj[maxn];

int dist[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    int pt = 1;
    int sz = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[pt];
        if (a[pt] == 0) {
            //ignore it
            continue;
        }
        int r = 0;
        ll cp = a[pt];
        while (cp > 0) {
            if (cp & 1) {
                cnt[r]++;
            }
            cp >>= 1;
            r++;
        }
        sz = max(sz,pt);
        pt++;
    }
    //cout << "sz = " << sz << '\n';
    for (int i = 0; i <= 62; i++) {
        if (cnt[i] >= 3) {
            cout << 3 << '\n';
            return 0;
        }
    }
    assert(n <= 200);
    for (int i = 1; i <= sz; i++) {
        for (int j = 1; j <= sz; j++) {
            if (i == j) continue;
            if ((a[i] & a[j]) != 0) {
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }
    }
    int minCycle = 999999;
    for (int i = 1; i <= sz; i++) {
        for (int j = i+1; j <= sz; j++) {
            if ((a[i] & a[j]) != 0) {
                for (int k = 1; k <= sz; k++) {
                    dist[k] = 999999;
                }
                dist[i] = 0;
                queue<int> q;
                q.push(i);
                while (!q.empty()) {
                    int f = q.front(); q.pop();
                    for (int k: adj[f]) {
                        if ((k == i && f == j) || (k == j && f == i)) continue;
                        if (dist[k] > dist[f] + 1) {
                            dist[k] = dist[f] + 1;
                            q.push(k);
                        }
                    }
                }
                //cout << i << ' ' << j << ": " << (dist[j]+1) << '\n';
                minCycle = min(minCycle,dist[j]+1);
            }
        }
    }
    cout << (minCycle == 999999 ? -1 : minCycle) << '\n';
}

