#include <bits/stdc++.h>
using namespace std;
using ll = long long;
 
const int maxn = 2e5+5;
int n;
string t;
map<int,vector<string>> mp;
ll START[maxn], END[maxn];
 
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
 
    ll hsh() {
        return prefix[len];
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
    cin >> t;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        mp[s.size()].push_back(s);
    }
    Hash ht(t);
    for (auto& p: mp) {
        int len = p.first;
        map<ll,int> cnt; //counts of hashes;
        for (auto& q: p.second) {
            cnt[Hash(q).hsh()]++;
        }
        for (int i = 1; i+len-1 <= t.size(); i++) {
            ll thash = ht.sub(i,i+len-1);
            if (cnt.count(thash)) {
                START[i] += cnt[thash];
                END[i+len-1] += cnt[thash];
            }
        }
    }
 
    ll res = 0;
    for (int i = 1; i < t.size(); i++) {
        res += END[i] * START[i+1];
    }
    cout << res << '\n';
}
