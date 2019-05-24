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
        vector<pair<ll,ll>> a1 = ps;
        sort(a1.begin(),a1.end(),[](pair<ll,ll> a, pair<ll,ll> b) {
                if (a.first != b.first) return a.first < b.first;
                return a.second < b.second;
                });
        vector<pair<ll,ll>> a2 = ps;
        sort(a2.begin(),a2.end(),[](pair<ll,ll> a, pair<ll,ll> b) {
                if (a.second != b.second) return a.second < b.second;
                return a.first < b.first;
                });
        set<vector<pair<ll,ll>>> ss;
        ss.insert(a1);
        ss.insert(a2);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (i == j) continue;
                if (ps[i].second >= ps[j].second &&
                    ps[i].first >= ps[j].first) continue;
                if (ps[j].first >= ps[i].first &&
                    ps[j].second >= ps[i].second) continue;
                ll num = ps[j].second-ps[i].second;
                ll den = ps[i].first-ps[j].first;
                if (num == 0 || den == 0) continue;
                if ((num < 0 && den < 0) || (num > 0 && den > 0)) {
                    if (num < 0) {
                        num *= -1;
                        den *= -1;
                    }
                    for (int a = -10; a <= 10; a++) {
                        for (int b = -10; b <= 10; b++) {
                            if (num+1 < 1 || den+b < 1) continue;
                            ll n = max(1LL,num+a);
                            ll d = max(1LL,den+b);

                            sort(ps.begin(),ps.end(),[n,d](auto a, auto b) {
                                return (n)*a.first + d*a.second < n*b.first + d*b.second;
                            });
                            if (valid(ps,n,d)) {
                                ss.insert(ps);
                            }
                        }
                    }
                }
            }
        }
        
        /*
        vector<pair<ll,ll>> p = ps;
        sort(p.begin(),p.end(),[](auto a, auto b) {
                return a.first*5+a.second*2 < b.first*5+b.second*2;
                });
        if (valid(p,5,2)) ss.insert(p);
        */
            
        /*
        for (auto p: ss) {
            pr(p);
        }
        */

        cout << ss.size() << '\n';
    }
}

