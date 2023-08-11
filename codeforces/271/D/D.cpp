#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;
typedef long long ll;

const int maxn = 2005;
bool good[26];

namespace HH {
    const int base = 29;
    const int M1 = 1e9+9;
    const int M2 = 1e9+21;
    ll inverse1[maxn], inverse2[maxn];
    int ctoi(char c) {return c-'a'+1;}

    ll modexp(ll x, ll n, int M) {
        if (n == 0) return 1;
        if (n == 1) return x%M;
        if (n%2==0) return modexp((x*x)%M,n/2,M);
        return (x*modexp((x*x)%M,n/2,M))%M;
    }

    struct Hash
    {
        int len;
        string str;
        ll *prefix1, *prefix2;
        Hash(const string& s) {
            len = s.size();
            str = s;
            prefix1 = new ll[maxn]; 
            prefix2 = new ll[maxn];
            prefix1[0] = 0;
            prefix2[0] = 0;
            ll mult1 = 1;
            ll mult2 = 1;
            for (int i = 0; i < s.size(); i++) {
                prefix1[i+1] = (prefix1[i] + (ctoi(s[i])*mult1)%M1)%M1;  
                mult1 = (mult1*base)%M1;

                prefix2[i+1] = (prefix2[i] + (ctoi(s[i])*mult2)%M2)%M2;  
                mult2 = (mult2*base)%M2;
            }
        }

        pair<ll,ll> sub(int l, int r) { //returns hash of [l,r] inclusive, 1-indexed
            return {((prefix1[r]-prefix1[l-1]+M1)*inverse1[l-1])%M1,
                    ((prefix2[r]-prefix2[l-1]+M2)*inverse2[l-1])%M2};
        }

        ~Hash() {
            delete[] prefix1;
            delete[] prefix2;
        }
    };

    void init_inverse() {
        inverse1[0] = 1;
        inverse1[1] = modexp(base,M1-2,M1);
        for (int i = 2; i < maxn; i++) {
            inverse1[i] = (inverse1[i-1] * inverse1[1]) % M1;
        }
        inverse2[0] = 1;
        inverse2[1] = modexp(base,M2-2,M2);
        for (int i = 2; i < maxn; i++) {
            inverse2[i] = (inverse2[i-1] * inverse2[1]) % M2;
        }   
    }
};
using namespace HH;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    init_inverse();
    string s; cin >> s;
    Hash h(s);
    for (int i = 1; i <= s.size(); i++) {
        //cout << i << ": " << h.prefix[i] << '\n';
    }
    for (int i = 0; i < 26; i++) {
        char c; cin >> c;
        good[i] = c == '1';
    }
    int k; cin >> k;
    int n = s.size();
    vector<pair<ll,ll>> hashes;
    for (int i = 0; i < n; i++) {
        int numBad = 0;
        for (int l = 1; i + l <= n; l++) {
            if (!good[s[i+l-1]-'a']) numBad++;
            if (numBad > k) break;
            hashes.push_back(h.sub(i+1,i+l));    
            //cout << s.substr(i,l) << ' ' << h.sub(i+1,i+l) << '\n';
        }
    }
    sort(hashes.begin(),hashes.end());
    hashes.erase(unique(hashes.begin(),hashes.end()),hashes.end());
    cout << hashes.size() << '\n';

    return 0;
}

