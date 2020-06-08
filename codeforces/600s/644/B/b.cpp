#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pi = pair<ll,ll>;

int n, b;
ll ans[200005];
map<ll,ll> mp;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> b;
    priority_queue<pi,vector<pi>,greater<pi>> pq;
    queue<pi> q;
    for (int i = 1; i <= n; i++) {
        ll t, d; cin >> t >> d;
        mp[t] = i;
        pq.push({t,d});
    }
    bool busy = false;
    while (!pq.empty()) {
        auto p = pq.top(); pq.pop();
        ll t = p.first;
        ll d = p.second;
        if (d > 0) {
            if (!busy) {
                busy = true;
                pq.push({t+d,0});
                ans[mp[t]] = t+d;
            }
            else {
                if (q.size() >= b) {
                    ans[mp[t]] = -1;
                }
                else {
                    q.push({t,d});
                }
            }
        }
        else {
            busy = false;
            if (!q.empty()) {
                busy = true;
                auto pp = q.front(); q.pop();
                pq.push({t+pp.second,0});
                ans[mp[pp.first]] = t+pp.second;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << ' ';
    }
    cout << '\n';
}
