#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <set>
using namespace std;
typedef long long ll;

int n;
ll p, q, b;

ll GCD(ll u, ll v) {
    while (v != 0) {
        ll r = u % v;
        u = v;
        v = r;
    }
    return u;
}

bool process(ll p, ll q, ll b) 
{
    if (p == 0) return true;
    ll gcd = GCD(p,q);
    p /= gcd;
    q /= gcd;
    ll x = GCD(q,b);
    while (x != 1) {
        while (q % x == 0) q /= x;
        x = GCD(q,b);
    }
    return (q == 1);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> p >> q >> b;
        //cout << "Processing # " << i << '\n';
        cout << (process(p,q,b) ? "Finite" : "Infinite") << '\n';
    }

   return 0;
}
	

