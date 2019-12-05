#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 105;
struct Event
{
    int t, d, p, id;
} events[maxn];
int n;

int dp[maxn][maxn*20];

vector<int> v;

int f(int i, int time) {
    if (i >= n) return 0;
    int& res = dp[i][time];
    if (res >= 0) return res;
    res = f(i+1,time);
    if (events[i].d > time + events[i].t) {
        res = max(res,events[i].p + f(i+1,time+events[i].t));
    }
    //printf("[%d][%d]: %d\n",i,time,res);
    return res;
}

void recon(int i, int time, int ans) {
    if (i >= n) return;
    if (ans == f(i+1,time)) {
        recon(i+1,time,ans);
    }
    else {
        v.push_back(i);
        recon(i+1,time+events[i].t,ans-events[i].p);
    }
}

int main() {
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> events[i].t >> events[i].d >> events[i].p;
        events[i].id = i+1;
    }
    sort(events,events+n,[](auto a, auto b) {
        return a.d != b.d ? a.d < b.d : a.t < b.t;
        });
    memset(dp,-1,sizeof dp);
    int ans = f(0,0);
    recon(0,0,ans);
    cout << ans << '\n';
    cout << v.size() << '\n';
    for (auto i: v) {
        cout << events[i].id << ' ';
    }
    cout << '\n';
}

