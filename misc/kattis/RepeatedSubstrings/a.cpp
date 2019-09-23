#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int base = 31;
const int M1 = 1e9+7;
const int M2 = 1e9+9;
const int maxn = 1e5+100;

ll inverse1[maxn], inverse2[maxn];
int ctoi(char c) {return c-'a'+1;}

ll modexp(ll x, ll n, ll M) {
    ll res = 1;
    while (n) {
        if (n&(1LL)) {
            res = (res*x) % M;
        }
        x = (x*x) % M;
        n >>= 1;
    }
    return res;
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
        prefix1[0] = 0; //important!
        ll mult = 1;
        for (int i = 0; i < s.size(); i++) {
            prefix1[i+1] = (prefix1[i] + (ctoi(s[i])*mult)%M1)%M1;
            mult = (mult*base)%M1;
        }
        prefix2 = new ll[maxn];
        prefix2[0] = 0; //important!
        mult = 1;
        for (int i = 0; i < s.size(); i++) {
            prefix2[i+1] = (prefix2[i] + (ctoi(s[i])*mult)%M2)%M2;
            mult = (mult*base)%M2;
        }   
    }

    pair<ll,ll> sub(int l, int r) { //returns hash of [l,r] inclusive, 1-indexed
        return {((prefix1[r]-prefix1[l-1]+M1)*inverse1[l-1])%M1,
                ((prefix2[r]-prefix2[l-1]+M2)*inverse2[l-1])%M2};
    }

    bool less(int l1, int r1, int l2, int r2) {
        assert(r1-l1 == r2-l2);
        if (sub(l1,r1) == sub(l2,r2)) return false;
        if (str[l1-1] != str[l2-1]) return str[l1-1] < str[l2-1];
        int len = r1-l1;
        int lo = 0, hi = len;
        while (lo + 1 < hi) {
            int mid = (lo+hi)/2;
            auto s1 = sub(l1,l1+mid);
            auto s2 = sub(l2,l2+mid);
            if (s1 == s2) {
                lo = mid;
            }
            else hi = mid;
        }
        return str[l1+lo] < str[l2+lo];
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

string s;
int n;

int get(int len, Hash& h) {
    map<pair<ll,ll>,int> cnt;
    int start = -1;
    for (int i = 0; i + len <= n; i++) {
        auto sub = h.sub(i+1,i+len);
        cnt[sub]++;
        if (cnt[sub] == 2) {
            if (start == -1 || h.less(i+1,i+len,start+1,start+len)) {
                start = i;
            }
        }
    }
    //cerr << len << ": " << start << '\n';
    return start;
}

int main() {
    srand(time(NULL));
    base = 31;// + (rand() % 50);
    init_inverse();
    cin >> s;
    n = s.size();
    Hash h = Hash(s);
    int lo = 0, hi = n;
    int start = -1;
    while (lo + 1 < hi) {
        int mid = (lo+hi)/2;
        int g = get(mid,h);
        if (g != -1) {
            lo = mid;
            start = g;
        }
        else hi = mid;
    }
    assert(start != -1);
    string ans = s.substr(start,lo);
    cout << ans << '\n';
}


