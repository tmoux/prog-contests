#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
int a[maxn];

ll modexp(ll x, ll n, int M) {
    if (n == 0) return 1;
    if (n == 1) return x%M;
    if (n%2==0) return modexp((x*x)%M,n/2,M);
    return (x*modexp((x*x)%M,n/2,M))%M;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, q; cin >> n >> q;
    while (q--) {
        int t; cin >> t;
        if (t == 1) {
            int i, k; cin >> i >> k;
            a[i] = k;
        }
        else {
            int p; cin >> p;
            map<int,int> mp;
            for (int i = 1; i <= p; i++) {
                mp[a[i]]++;
            }
            const int M = 1e9+7;
            ll c = 1;
            for (auto& p: mp) {
                c = (c * modexp(p.second+1,p.second+1,M)) % M;                    
            }
            cout << c << '\n';
        }
    }

    return 0;
}

