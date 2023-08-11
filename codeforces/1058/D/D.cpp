#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    ll n, m, k; cin >> n >> m >> k;
    if ((2*n*m) % k != 0) {
        //not possible
        cout << "NO\n";
        return 0;
    }
    bool isEven = k % 2 == 0;
    if (isEven) k/= 2;
    ll a = n/__gcd(k,n);
    k = k/__gcd(k,n);
    ll b = m/k;
    if (!isEven) {
        if (a < n) a = 2*a;
        else b = 2*b;
    }
    cout << "YES\n";
    cout << "0 0\n";
    cout << a << " 0\n";
    cout << "0 " << b << '\n';
    
    return 0;
}

