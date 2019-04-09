#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1005;
struct Cashier
{
    ll cap, time, extra;
} cashiers[maxn];

void solve(int qq) {
    ll R, B, C; cin >> R >> B >> C;
    for (int i = 0; i < C; i++) {
        cin >> cashiers[i].cap >> cashiers[i].time >> cashiers[i].extra;
        //printf("cap = %d, time = %d, extra = %d\n",cashiers[i].cap,cashiers[i].time,cashiers[i].extra);
    }
    ll lo = 0, hi = LLONG_MAX;
    while (lo + 1 < hi) {
        ll mid = (lo+hi)/2;
        vector<ll> bits;
        for (int i = 0; i < C; i++) {
            ll num = max(0LL,(mid-cashiers[i].extra)/cashiers[i].time);
            bits.push_back(min((ll)cashiers[i].cap,num));
        }
        sort(bits.begin(),bits.end(),greater<ll>());
        /*
        cout << mid << ":\n";
        for (ll i: bits) {
            cout << i << '\n';
        }
        */
        ll tot = 0;
        for (int i = 0; i < R; i++)
            tot += bits[i];
        if (tot >= B) hi = mid;
        else lo = mid;
    }
    cout << "Case #" << qq << ": " << hi << '\n';
}

int main()
{
    int t; cin >> t;
    for (int qq = 1; qq <= t; qq++) {
        solve(qq);
    }
}

