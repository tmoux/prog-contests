#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll intersect(ll l1, ll r1, ll l2, ll r2) {
    return max(0LL,min(r1,r2)-max(l1,l2)+1);
}

ll solve(ll la, ll ra, ll lb, ll rb, ll gc) {
    lb -= la;
    rb -= la;
    ra -= la;
    la = 0;

    lb += 1000000000*gc;
    rb += 1000000000*gc;

    assert(lb >= 0);
    ll minus = lb - (lb%gc);
    lb -= minus;
    rb -= minus;
    //printf("[%d, %d], [%d, %d]\n",la,ra,lb,rb);
    return intersect(la,ra,lb,rb);
}

int main() {
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    ll la, ra, ta; cin >> la >> ra >> ta;
    ll lb, rb, tb; cin >> lb >> rb >> tb;
    ll gc = __gcd(ta,tb);

    ll ans = solve(la,ra,lb,rb,gc);
    ans = max(ans,solve(lb,rb,la,ra,gc)); 
    cout << ans << '\n';
}

