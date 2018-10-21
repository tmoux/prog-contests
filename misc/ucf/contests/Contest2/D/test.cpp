#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <cstring>
using namespace std;
typedef long long ll;

string a, b, c;
const int base = 29;
const int M = 1e9+7;
const int maxn = 400010;

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

    ll sub(int l, int r) {
        //returns hash of [l,r] inclusive
        return ((prefix[r]-prefix[l-1]+M)*inverse[l-1])%M;
    }

    bool isSubstr(const Hash& other) {
        //checks if other is a substring of itself
        for (int l = 1; l + other.len - 1 <= len; l++) {
            int r = l + other.len - 1;
            if (other.prefix[other.len] == sub(l,r)) {
                return true;
            }
        }
        return false;
    }

    ~Hash() {
        delete[] prefix;
    }
};

void combine(Hash& h1, Hash& h2) {
    int l = min(h1.len,h2.len);
    for (int i = l; i >= 0; i--) {
        if (i == 0) {
            h1.addRight(h2.str.substr(0,h2.len));
            return;
        }
        if (h1.sub(h1.len-i+1,h1.len) == h2.sub(1,i)) {
            h1.addRight(h2.str.substr(i));    
            return;
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> a >> b >> c;
    vector<string> ss = {a,b,c};
    inverse[0] = 1;
    inverse[1] = modexp(base,M-2);
    for (int i = 2; i < maxn; i++) {
        inverse[i] = (inverse[i-1] * inverse[1]) % M;
    }

    int minlen = 9999999;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                if (i != j && i != k && j != k) {
                    Hash h1(ss[i]), h2(ss[j]), h3(ss[k]);
                    if (h1.isSubstr(h2)) h2.len = 0;
                    if (h1.isSubstr(h3) || h2.isSubstr(h3)) h3.len = 0;
                    combine(h1,h2);
                    combine(h1,h3);
                    minlen = min(minlen,h1.len);
                }
            }
        }
    }
    cout << minlen << '\n';
    
    return 0;
}
