#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
const ll INF = 1LL<<61;
int n;
ll dp[maxn][10];
vector<pair<ll,ll>> turn[maxn]; //{cost, damage}

ll normal(int card, const vector<pair<ll,ll>>& ref) {
    if (card == 1) {
        ll mxd = 0;
        for (auto p: ref) {
            mxd = max(mxd,p.second);
        }
        return mxd;
    }
    else if (card == 3) {
        vector<ll> os;
        for (auto p: ref) {
            if (p.first == 1) os.push_back(p.second);
        }
        sort(os.begin(),os.end(),greater<ll>());
        if (os.size() < 3) return -INF;
        return os[0] + os[1] + os[2];
    }
    else if (card == 2) {
        vector<ll> ones, twos;
        for (auto p: ref) {
            if (p.first == 1) ones.push_back(p.second);
            else if (p.first == 2) twos.push_back(p.second);
        }
        if (ones.size() + twos.size() < 2 || ones.empty()) {
            return -INF;
        }
        sort(ones.begin(),ones.end(),greater<ll>());
        sort(twos.begin(),twos.end(),greater<ll>());
        ll mxd = 0;
        if (!ones.empty() && !twos.empty()) {
            mxd = max(mxd,ones[0] + twos[0]);
        }
        if (ones.size() >= 2) {
            mxd = max(mxd,ones[0] + ones[1]);
        }
        return mxd;
    }
    assert(false);
    return 0;
}

ll special(int card, const vector<pair<ll,ll>>& ref) {
    if (card == 1) {
        ll mxd = 0;
        for (auto p: ref) {
            mxd = max(mxd,p.second);
        }
        return 2*mxd;
    }
    else if (card == 3) {
        vector<ll> os;
        for (auto p: ref) {
            if (p.first == 1) os.push_back(p.second);
        }
        sort(os.begin(),os.end(),greater<ll>());
        if (os.size() < 3) return -INF;
        return 2*os[0] + os[1] + os[2];
    }
    else if (card == 2) {
        vector<ll> ones, twos;
        for (auto p: ref) {
            if (p.first == 1) ones.push_back(p.second);
            else if (p.first == 2) twos.push_back(p.second);
        }
        if (ones.size() + twos.size() < 2 || ones.empty()) {
            return -INF;
        }
        sort(ones.begin(),ones.end(),greater<ll>());
        sort(twos.begin(),twos.end(),greater<ll>());
        ll mxd = 0;
        if (!ones.empty() && !twos.empty()) {
            vector<ll> vv = {ones[0],twos[0]};
            sort(vv.begin(),vv.end(),greater<ll>());
            ll tr = 2*vv[0] + vv[1];
            mxd = max(mxd,tr);
        }
        if (ones.size() >= 2) {
            mxd = max(mxd,2*ones[0] + ones[1]);
        }
        return mxd;
    }
    assert(false);
    return 0;
}

ll f(int i, int num) {
    if (dp[i][num] >= 0) return dp[i][num];
    if (i > n) return 0;
    dp[i][num] = f(i+1,num);
    for (int card = 1; card <= 3; card++) {
        if (num - card < 0) {
            dp[i][num] = max(dp[i][num],
                         special(card,turn[i]) + f(i+1,(num-card+10) % 10));
        }
        else {
            dp[i][num] = max(dp[i][num],
                         normal(card,turn[i]) + f(i+1,(num-card+10) % 10));
        }
    }
    return dp[i][num];
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int ki; cin >> ki;
        while (ki--) {
            int c, d; cin >> c >> d;
            turn[i].push_back({c,d});
        }
    }
    memset(dp,-1,sizeof dp);
    ll ans = f(1,9);
    cout << ans << '\n';
}

