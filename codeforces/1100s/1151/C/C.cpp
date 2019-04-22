#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int M = 1e9+7;
//what is the place (order) of the n'th odd/even number?

ll getOddOrd(ll x) {
    ll curr = 0;
    ll mult = 1;
    ll cnt = 0;    
    while (curr < x) {
        curr += mult;
        curr += 2*mult;
        mult *= 4;
    }
    return curr;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    //ll l, r; cin >> l >> r;
    int x; cin >> x;
    cout << getOddOrd(x) << '\n';
}

