#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll phi(ll n) 
{ 
    ll result = n; // Initialize result as n 
  
    // Consider all prime factors of n and subtract their 
    // multiples from result 
    for (ll p = 2; p * p <= n; ++p) { 
          
        // Check if p is a prime factor. 
        if (n % p == 0) { 
              
            // If yes, then update n and result 
            while (n % p == 0) 
                n /= p; 
            result -= result / p; 
        } 
    } 
  
    // If n has a prime factor greater than sqrt(n) 
    // (There can be at-most one such prime factor) 
    if (n > 1) 
        result -= result / n; 
    return result; 
} 

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        ll a, m; cin >> a >> m;
        ll gc = __gcd(a,m);
        m /= gc;
        cout << phi(m) << endl;
    }
}

