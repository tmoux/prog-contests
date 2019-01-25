#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5, maxm = 305, maxk = 17;
int n, m;

typedef pair<int,int> pii;
pii interval[maxm];
int a[maxn];
int mn[maxk][maxn];

inline bool contains(pii& a, int i) {
    return a.first <= i && i <= a.second;
}

inline int lg(int x) { return 32 - __builtin_clz(x) - 1; }

int getmin(int l, int r) {
    assert(1 <= l && l <= r && r <= n);
    int g = lg(r-l+1);
    return min(mn[g][l],mn[g][r-(1<<g)+1]);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int ai; cin >> ai;
        a[i] = ai;
        mn[0][i] = ai;
    }
    //fill sparse table
    for (int k = 1; k < maxk; k++) {
        for (int i = 1; i <= n; i++) {
            int nx = i + (1<<(k-1));
            if (nx > n) mn[k][i] = mn[k-1][i];
            else mn[k][i] = min(mn[k-1][i],mn[k-1][nx]);
        }
    }
    for (int i = 1; i <= m; i++) {
        cin >> interval[i].first >> interval[i].second;
    }

    pair<int,vector<int>> ans = {0,{}};
    for (int i = 1; i <= n; i++) {
        vector<int> ret;
        map<int,pii> mp; //x coordinate of starts and ends
        for (int j = 1; j <= m; j++) {
            if (!contains(interval[j],i)) {
                ret.push_back(j);
                mp[interval[j].first].first++;
                mp[interval[j].second].second++;
            }
        }
    }
    cout << ans.first << '\n';
    cout << ans.second.size() << '\n';
    for (int i: ans.second) {
        cout << i << ' ';
    }
    cout << '\n';


    return 0;
}

