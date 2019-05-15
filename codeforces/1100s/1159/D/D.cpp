#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
const int base = 29;
const int M = 1e9+7;

ll inverse[maxn];
int ctoi(char c) {return c-'a'+1;}

ll modexp(ll x, ll n) {
    if (n == 0) return 1;
    if (n == 1) return x%M;
    if (n%2==0) return modexp((x*x)%M,n/2);
    return (x*modexp((x*x)%M,n/2))%M;
}

struct Hash
{
    int len;
    string str;
    ll* prefix;
    Hash(const string& s) {
        len = s.size();
        str = s;
        prefix = new ll[maxn];
        prefix[0] = 0; //important!
        ll mult = 1;
        for (int i = 0; i < s.size(); i++) {
            prefix[i+1] = (prefix[i] + (ctoi(s[i])*mult)%M)%M;  
            mult = (mult*base)%M;
        }
    }

    void addRight(const string& s) {
        ll mult = modexp(base,len);
        for (int i = len+1; i <= len+s.size(); i++) {
            prefix[i] = (prefix[i-1] + (ctoi(s[i-len-1])*mult%M))%M;
            mult = (mult*base)%M;
        }
        len += s.size();
    }

    ll sub(int l, int r) { //returns hash of [l,r] inclusive, 1-indexed
        return ((prefix[r]-prefix[l-1]+M)*inverse[l-1])%M;
    }

    ~Hash() {
        delete[] prefix;
    }
};

void init_inverse() {
    inverse[0] = 1;
    inverse[1] = modexp(base,M-2);
    for (int i = 2; i < maxn; i++) {
        inverse[i] = (inverse[i-1] * inverse[1]) % M;
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    init_inverse();
    int n, k; cin >> n >> k;

}

