#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    ll w, m; cin >> w >> m;
    //base w
    vector<ll> v;
    while (m) {
        v.push_back(m%w);
        m /= w;
    }
    for (int i = 0; i < v.size(); i++) {
        
    }
}
