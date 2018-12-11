#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ll;

void mod(ll& a, ll n) {
    while (a < 0) a += n;
}

pair<ll,pair<ll,ll>> gcd(ll a, ll b) {
    if (a == 0) return {b,{0,1}};
    if (b == 0) return {a,{1,0}};
    ll x1 = 1, x2 = 0, y1 = 0, y2 = 1;
    while (a && b) {
        ll r = a/b;
        ll tmp = b;
        b = a - r * b;
        //mod(b);
        a = tmp;
        ll tmpx = x2, tmpy = y2;
        x2 = x1 - r * x2;
        y2 = y1 - r * y2;
        //mod(x2);
        //mod(y2);
        x1 = tmpx, y1 = tmpy;
        //printf("%d: %d, %d\n",b,x2,y2);
    }
    //printf("%d %d %d\n",a,x1,y1);
    return {a,{x1,y1}};
}

ll mod_inverse(ll x, ll n) { //must check that x and n are coprime!!!
    pair<ll,pair<ll,ll>> ans = gcd(x,n);
    while (ans.second.first < 0) ans.second.first += n;
    return ans.second.first;
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    ll a, b; cin >> a >> b;
    cout << mod_inverse(a,b) << '\n';

    return 0;
}

