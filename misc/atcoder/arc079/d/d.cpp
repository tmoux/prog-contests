#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll a[55];

ll solve() {
    ll res = 0;
    while (true) {
        ll tr = -1;
        for (int i = 0; i < 50; i++) {
            tr = max(tr,a[i]);
        }
        if (tr < 50) break;
        res++;
        pair<ll,int> mx = {-1,-1};
        for (int i = 0; i < 50; i++) {
            mx = max(mx,{a[i],i});
        }
        for (int i = 0; i < 50; i++) {
            if (i != mx.second) a[i]++;
            else a[i] -= 50;
            assert(a[i] >= 0);
        }
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    ll k; cin >> k;
    ll d = k/50;
    ll r = k%50;
    for (int i = 0; i < 50; i++) {
        a[i] = d+i;
    }
    int i = 0;
    while (r--) {
        for (int j = 0; j < 50; j++) {
            if (j == i) a[j] += 50;
            else a[j]--;
        }
        i = (i+1)%50;
    }
    cout << 50 << '\n';
    for (int j = 0; j < 50; j++) {
        cout << a[j] << ' ';
    }
    cout << '\n';
    //assert(solve() == k);
}

