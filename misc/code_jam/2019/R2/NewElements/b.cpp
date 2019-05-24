#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void pr(vector<pair<ll,ll>> a) {
    for (auto p: a) {
        cout << p.first << ' ' << p.second << '\n';
    }
    cout << "\n";
}

bool valid(const vector<pair<ll,ll>>& v, ll a, ll b) {
    for (int i = 0; i < v.size() - 1; i++) {
        if (v[i].first * a + v[i].second * b == v[i+1].first * a + v[i+1].second * b) return false;
    }
    return true;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    for (int aa = 1; aa <= t; aa++) {
        cout << "Case #" << aa << ": ";
        int N; cin >> N;
        vector<pair<ll,ll>> ps;
        for (int i = 0; i < N; i++) {
            int a, b; cin >> a >> b;
            ps.push_back({a,b});
        }
        set<pair<ll,ll>> ss;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (i == j) continue;
                ll num = ps[i].first - ps[j].first;
                ll den = ps[j].second - ps[i].second;
                if (den != 0 && double(num)/den > 0) {
                    ll gc = __gcd(num,den);
                    num /= gc;
                    den /= gc;
                    ss.insert({num,den});
                }
            }
        }
        /*
        for (auto p: ss) {
            cout << p.first << ' ' << p.second << '\n';
        }
        */
        cout << (ss.size()+1) << '\n';
    }
}

