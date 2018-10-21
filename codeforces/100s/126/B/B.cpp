#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e6+5, base = 31, M = 1e9+9;
ll inverse[maxn];
inline int ctoi(char c) {return c-'a'+1;}
ll modexp(ll x, ll n) {
    if (n == 0) return 1;
    if (n == 1) return x%M;
    if (n%2==0) return modexp((x*x)%M,n/2);
    return (x*modexp((x*x)%M,n/2))%M;
}

void getInverse() {
    inverse[0] = 1LL;
    inverse[1] = modexp(base,M-2);
    for (int i = 2; i < maxn; i++) {
        inverse[i] = (inverse[i-1] * inverse[1]) % M;
    }
}

struct Hash
{
    int len;
    ll* prefix;
    Hash(const string& s) {
        len = s.size();
        prefix = new ll[maxn];
        ll mult = 1;
        for (int i = 0; i < len; i++) {
            prefix[i+1] = (prefix[i] + (ctoi(s[i])*mult)%M)%M;
            mult = (mult*base)%M;
        }
    }
    ll sub(int l, int r) {
        return ((prefix[r]-prefix[l-1]+M)*inverse[l-1])%M;
    }
    bool contains(ll h, int sz) {
        for (int i = 2; i + sz - 1 < len; i++) {
            if (sub(i,i+sz-1) == h) return true;
        }
        return false;
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    string s; cin >> s;
    Hash h(s);
    getInverse();
    for (int l = h.len - 2; l >= 1; --l) {
        if (h.sub(1,l) == h.sub(h.len-l+1,h.len) && h.contains(h.sub(1,l),l)) {
            cout << s.substr(0,l) << '\n';
            return 0;
        }
    }
    cout << "Just a legend\n";
    return 0;
}
	

