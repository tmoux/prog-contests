#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll need[3], curr[3], price[3];
ll r;

bool isValid(ll x) {
    ll c = 0;
    for (int i = 0; i < 3; i++) {
        c += max(0LL,(need[i]*x - curr[i])*price[i]);
    }
    return c <= r;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    //read input
    string s; cin >> s;
    for (char c: s) {
        if (c == 'B') need[0]++;
        else if (c == 'S') need[1]++;
        else need[2]++;
    }
    cin >> curr[0] >> curr[1] >> curr[2];
    cin >> price[0] >> price[1] >> price[2];
    cin >> r;

    //binary search
    ll lo = 0, hi = 1e14;
    while (lo + 1 < hi) {
        ll mid = (lo + hi)/2;
        if (!isValid(mid)) {
            hi = mid;
        }
        else {
            lo = mid;
        }
    }
   
    cout << lo << '\n';

    return 0;
}
	

