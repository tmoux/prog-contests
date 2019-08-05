#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
const ll INF = 1LL<<50;
int n, m, k, q;

vector<int> treasures[maxn]; //cols of treasures on this row
vector<int> safe;

ll dp[maxn][2];
int l[maxn], r[maxn];

ll calc(ll l, ll r, ll curr) {
    if (l <= r) {
        if (curr <= r) {
            return abs(r-l)+abs(r-curr);
        }
        else return abs(curr-l);
    }
    else {
        if (curr >= r) {
            return abs(l-r)+abs(curr-r);            
        }
        else {
            return abs(l-curr);
        }
    }
}

void update(ll& res, ll prev, ll dist, ll d2) {
    res = min(res,(ll)prev+dist+d2);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m >> k >> q;
    int maxRow = 0;
    for (int i = 0; i < k; i++) {
        int r, c; cin >> r >> c;
        treasures[r].push_back(c);
        maxRow = max(maxRow,r);
    }
    for (int i = 1; i <= n; i++) {
        sort(treasures[i].begin(),treasures[i].end());
        if (!treasures[i].empty()) {
            l[i] = treasures[i][0];
            r[i] = treasures[i].back();
        }
    }
    for (int i = 0; i < q; i++) {
        int b; cin >> b;
        safe.push_back(b);
    }
    sort(safe.begin(),safe.end());
    if (treasures[1].empty()) {
        r[1] = 1;
    }
    dp[1][0] = INF;
    dp[1][1] = r[1]-1;
    for (int i = 2; i <= maxRow; i++) {
        if (l[i] == 0 && r[i] == 0) {
            dp[i][0] = dp[i-1][0]+1;
            dp[i][1] = dp[i-1][1]+1;
            l[i] = l[i-1];
            r[i] = r[i-1];
        }
        else {
            dp[i][0] = dp[i][1] = INF;
            //cout << l[i-1] << ' ' << r[i-1] << '\n';
            auto it = lower_bound(safe.begin(),safe.end(),l[i-1]);
            if (it != safe.end()) {
                ll dist = abs(*it-l[i-1]);
                update(dp[i][0],dp[i-1][0],dist+1,calc(l[i],r[i],*it));
                update(dp[i][1],dp[i-1][0],dist+1,calc(r[i],l[i],*it));
            }
            if (it != safe.begin()) {
                --it;
                ll dist = abs((*it)-l[i-1]);
                //cout << (dp[i-1][0]+dist+1+calc(l[i],r[i],*it));
                update(dp[i][0],dp[i-1][0],dist+1,calc(l[i],r[i],*it));
                update(dp[i][1],dp[i-1][0],dist+1,calc(r[i],l[i],*it));
            }
            //cout << dp[i][0] << '\n';
            //now try right side
            it = lower_bound(safe.begin(),safe.end(),r[i-1]);
            if (it != safe.end()) {
                ll dist = abs(*it-r[i-1]);
                update(dp[i][0],dp[i-1][1],dist+1,calc(l[i],r[i],*it));
                update(dp[i][1],dp[i-1][1],dist+1,calc(r[i],l[i],*it));
            }
            if (it != safe.begin()) {
                --it;
                ll dist = abs(*it-r[i-1]);
                //cout << *it << ' ' << r[i-1] << '\n';
                //cout << dp[i-1][1] << '\n';
                //cout << dp[i-1][1] << ' ' << (dist+1) << ' ' << calc(l[i],r[i],*it) << '\n';
                update(dp[i][0],dp[i-1][1],dist+1,calc(l[i],r[i],*it));
                update(dp[i][1],dp[i-1][1],dist+1,calc(r[i],l[i],*it));
            }
        }
        //cout << i << ": " << dp[i][0] << ' ' << dp[i][1] << '\n';
    }
    
    ll ans = min(dp[maxRow][0],dp[maxRow][1]);
    cout << ans << '\n';
}

