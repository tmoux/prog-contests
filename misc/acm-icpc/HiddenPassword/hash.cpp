#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int base = 29;
const int M = 1e9+7;
const int maxn = 2e5+100;

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
        str = '#' + s; //to make str 1-indexed
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

    ll sub(int l, int r) { //returns hash of [l,r] inclusive, 1-indexed
        return ((prefix[r]-prefix[l-1]+M)*inverse[l-1])%M;
    }

    bool comp(int a, int b, int n) { //compare s[a..a+n] to s[b..b+n]
        if (str[a] != str[b]) return str[a] < str[b];
        int lo = 0, hi = n;
        while (lo + 1 < hi) {
            int m = (lo+hi)>>1;
            if (sub(a,a+m) == sub(b,b+m)) {
                lo = m;        
            }
            else hi = m;
        }
        if (lo == n - 1) {
            return a < b;    
        }
        return str[a+lo+1] < str[b+lo+1];
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
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    init_inverse();
    int t; cin >> t;
    while (t--) {
        int n; string s; cin >> n >> s;
        s += s;
        Hash h(s);
        vector<int> v(n);
        for (int i = 1; i <= n; i++) v[i-1] = i;
        //apparently stable_sort is faster than sort??? 1.12 vs 1.77 seconds?
        stable_sort(v.begin(),v.end(),[&h,n](int a, int b) {
            return h.comp(a,b,n); 
        });
        cout << v[0]-1 << '\n';
        /*
        for (int i: v) {
            cout << i << ' ' << s.substr(i-1,n) << '\n';
        }
        */
        /*
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                cout << s.substr(i-1,n) << ' ' << s.substr(j-1,n) << ' ' << h.comp(i,j,n) << '\n';
            }
        }
        */
    }

    return 0;
}

