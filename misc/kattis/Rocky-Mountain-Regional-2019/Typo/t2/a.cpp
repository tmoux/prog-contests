#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//problem is cancer
//seems double hash is necessary
//Need to keep updated double hash template
//for ICPC especially
const int maxn = 1e6+100;

namespace HH {
    int base = 29;
    const int M1 = 1e9+9;
    const int M2 = 1e9+21;
    ll inverse1[maxn], inverse2[maxn], power1[maxn], power2[maxn];
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
            prefix1 = new ll[s.size()+5]; 
            prefix2 = new ll[s.size()+5];
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

        power1[0] = 1;
        for (int i = 1; i < maxn; i++) {
            power1[i] = (base*power1[i-1]) % M1;
        }
        power2[0] = 1;
        for (int i = 1; i < maxn; i++) {
            power2[i] = (base*power2[i-1]) % M2;
        }
    }
};
using namespace HH;

int n;
string s[maxn];
vector<Hash> h;

pair<ll,ll> shift(pair<ll,ll> h, ll x) {
    return {(h.first*power1[x])%M1,(h.second*power2[x])%M2};
}

pair<ll,ll> operator+(pair<ll,ll> l, pair<ll,ll> r) {
    return {(l.first+r.first)%M1,(l.second+r.second)%M2};
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    random_device device;
    mt19937 gen(device());
    base = 31 + (gen() % 1000);
    init_inverse();
    /*
    Hash aa = Hash("ASDF");
    for (int i = 1; i <= 4; i++) {
        for (int j = i; j <= 4; j++) {
            cout << i << ' ' << j << ": " << aa.sub(i,j) << endl;
        }
    }
    */
    cin >> n;
    set<pair<ll,ll>> hashes;
    for (int i = 0; i < n; i++) {
        cin >> s[i];
        Hash hh = Hash(s[i]);
        h.push_back(hh);
        hashes.insert(h[i].sub(1,s[i].size()));
    }

    /*
    for (int i = 0; i < n; i++) {
        cout << i << ": " << h[i].prefix[s[i].size()] << endl;
    }
    */

    vector<string> ans;
    for (int i = 0; i < n; i++) {
        //cout << i << ": " << s[i] << ", " << "sz = " << s[i].size() << endl;
        bool poss = false;
        int sz = s[i].size();
        if (sz == 1) continue;
        poss |= hashes.count(h[i].sub(1,sz-1));
        poss |= hashes.count(h[i].sub(2,sz));
        for (int j = 2; j < sz; j++) {
            //cout << "str = " << s[i] << ", calling " << i << ", sz = " << sz << endl;
            pair<ll,ll> tr = h[i].sub(1,j-1);
            tr = tr + shift(h[i].sub(j+1,sz),j-1);
            poss |= hashes.count(tr);
            //cout << j << ": " << tr << endl;
            if (poss) break;
        }
        if (poss) ans.push_back(s[i]);
    }
    //output
    //
    if (ans.empty()) {
        cout << "NO TYPOS\n";
        return 0;
    }
    for (auto s: ans) {
        cout << s << '\n';
    }
}

