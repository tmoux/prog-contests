#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 5005;
vector<int> cand[maxn], repl[maxn];
int n, m;
int t[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    //just simualte it lol
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int ai, bi; cin >> ai >> bi;
        cand[ai].push_back(bi);
    }
    for (int i = 1; i <= n; i++) {
        if (cand[i].empty()) {
            t[i] = 0;
            continue;
        }
        else {
            int ret = i;
            int dist = n+1;
            for (int j: cand[i]) {
                int d = j > i ? j-i : n - (i-j);
                if (d < dist) {
                    dist = d;
                    ret = i;
                }
            }
            t[i] = ((int)cand[i].size()-1) * n + dist;
            //cout << i << ": " << t[i] << '\n';
        }
    }

    for (int i = 1; i <= n; i++) {
        vector<int> times;
        int mx = 0;
        for (int j = 0; j < n; j++) {
            int idx = i + j <= n ? i + j : i + j - n;
            if (t[idx] > 0) times.push_back(t[idx] + j);
        }
        for (int j: times) {
            mx = max(mx,j);
        }
        cout << mx << '\n';
    }
}

