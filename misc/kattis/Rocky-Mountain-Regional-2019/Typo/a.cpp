#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int base;
int mods[] = {998244353,1000000009,1000000007};
int M = 1e9+9;
const int maxn = 1e6+100;

ll inverse[maxn];
ll power[maxn];
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
    vector<ll> prefix;
    Hash() {}
    Hash(const string& s) {
        //cout << s << endl;
        len = s.size();
        str = s;
        prefix.resize(s.size()+3);
        prefix[0] = 0; //important!
        ll mult = 1;
        for (int i = 0; i < s.size(); i++) {
            prefix[i+1] = (prefix[i] + (ctoi(s[i])*mult)%M)%M;  
            mult = (mult*base)%M;
        }
    }

    ll sub(int l, int r) { //returns hash of [l,r] inclusive, 1-indexed
        /*
        cout << str << endl;
        cout << l << ' ' << r << endl;
        */
        assert(0 <= l-1 && r <= str.size());
        return ((prefix[r]-prefix[l-1]+M)*inverse[l-1])%M;
    }
};

void init_inverse() {
    inverse[0] = 1;
    inverse[1] = modexp(base,M-2);
    for (int i = 2; i < maxn; i++) {
        inverse[i] = (inverse[i-1] * inverse[1]) % M;
    }
    power[0] = 1;
    for (int i = 1; i < maxn; i++) {
        power[i] = (base*power[i-1]) % M;
    }
}

int n;
string s[maxn];
vector<Hash> h;

ll shift(ll h, ll x) {
    return (h*power[x]) % M;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    random_device device;
    mt19937 gen(device());
    base = 31 + (gen() % 1000);
    M = mods[gen()%3];
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
    set<ll> hashes;
    for (int i = 0; i < n; i++) {
        cin >> s[i];
        Hash hh = Hash(s[i]);
        h.push_back(hh);
        hashes.insert(h[i].prefix[s[i].size()]);
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
            ll tr = h[i].sub(1,j-1);
            tr += shift(h[i].sub(j+1,sz),j-1);
            tr %= M;
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

