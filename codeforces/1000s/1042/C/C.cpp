#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void pf(vector<pair<int,int>>& v) {
    if (v.empty()) return;
    for (int i = 0; i < v.size() - 1; i++) {
        cout << 1 << ' ' << v[i].second << ' ' << v[i+1].second << '\n';
    }
}

void join(vector<pair<int,int>>& u, vector<pair<int,int>>& v) {
    if (u.empty() || v.empty()) return;
    cout << 1 << ' ' << u.back().second << ' ' << v.back().second << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    vector<pair<int,int>> pos, zero, neg;
    int n; cin >> n;
    for (int i = 1; i <= n; i++) {
        int ai; cin >> ai;
        if (ai > 0) pos.push_back({abs(ai),i});
        else if (ai == 0) zero.push_back({abs(ai),i});
        else neg.push_back({abs(ai),i});    
    }
    sort(pos.begin(),pos.end());
    sort(zero.begin(),zero.end());
    sort(neg.begin(),neg.end());
    if (zero.size() == 0) {
        if (neg.size() % 2 == 0) {
            pf(pos);
            pf(neg);
            join(pos,neg);
        }
        else {
            if (!neg.empty()) {
                cout << 2 << ' ' << neg.begin()->second << '\n';
                neg.erase(neg.begin());
            }
            pf(pos);
            pf(neg);
            join(pos,neg);
        }
    }
    else {
        if (neg.size() % 2 == 0) {
            pf(zero);
            pf(pos);
            pf(neg);
            join(pos,neg);
            if (!(pos.empty() && neg.empty())) cout << 2 << ' ' << zero.back().second << '\n';
        }
        else {
            if (!pos.empty()) {
                pf(zero);
                cout << 1 << ' ' << zero.back().second << ' ' << neg.front().second << '\n';
                cout << 2 << ' ' << neg.front().second << '\n';
                neg.erase(neg.begin());
                pf(neg);
                pf(pos);
                join(pos,neg);
                
            }
            else {
                pf(zero);
                cout << 1 << ' ' << zero.back().second << ' ' << neg.front().second << '\n';
                if (neg.size() > 1) {
                    cout << 2 << ' ' << neg.front().second << '\n';
                    neg.erase(neg.begin());
                    pf(neg);
                }
            }
        }
    }

    return 0;
}

