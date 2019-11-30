#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxm = 2e5+5, maxn = 85;
int n, m;

struct Interval
{
    int x, s, l, r;
};

vector<Interval> v;
bool used[maxm];
const int INF = 2e9+9;

int dp[maxm];
void amin(int& a, int b) {
    a = min(a,b);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    vector<Interval> vs;
    for (int i = 0; i < n; i++) {
        int x, s; cin >> x >> s;
        vs.push_back({x,s,x-s,x+s});
    }
    sort(vs.begin(),vs.end(),[](auto a, auto b) {
            return a.l != b.l ? a.l < b.l : a.r > b.r;
            });
    for (int i = 0; i < n; i++) {
        if (!v.empty() && vs[i].r <= v.back().r) {
            continue;
        }
        else {
            v.push_back(vs[i]);
        }
    }
    n = v.size();
    for (auto p: v) {
        for (int i = max(1,p.l); i <= min(m,p.r); i++) {
            used[i] = true;
        }
    }
    dp[m] = 0;
    for (int i = m-1; i >= 0; i--) {
        dp[i] = m-i;
        if (used[i+1]) amin(dp[i],dp[i+1]);
        for (auto p: v) {
            if (i < p.l) {
                int d = p.l-i-1;
                amin(dp[i],d+dp[min(m,p.r+d)]);
            }
        }
    }
    cout << dp[0] << '\n';
}

