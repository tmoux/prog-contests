#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll floor(ll a, ll b) {
    if (a % b == 0) return a/b-1;
    if ((a<0) == (b<0)) {
        return a/b;
    }
    return a/b-1;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    ll p;
    int k;
    cin >> p >> k;
    vector<ll> a;
    while (true) {
        ll aj = a.empty() ? p : a.back();
        ll ai = floor(k-aj,k);
        a.push_back(ai);
        //cout << ai << endl;
        if (ai == 0) break;
    }
    vector<ll> ret;
    for (int i = 0; i < a.size(); i++) {
        ret.push_back((i==0?p:a[i-1])+k*a[i]);
        assert(ret.back() < k);
    }
    cout << ret.size() << '\n';
    for (auto i: ret) {
        cout << i << ' ';
    }
    cout << '\n';
}

