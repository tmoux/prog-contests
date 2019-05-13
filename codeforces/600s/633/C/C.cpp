#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e4+4;
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

    ll sub(int l, int r) { //returns hash of [l,r] inclusive, 1-indexed
        return ((prefix[r]-prefix[l-1]+M)*inverse[l-1])%M;
    }

    ll gethash() {
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

int n, m;
string s;
map<string,string> actual;
map<int,vector<string>> words;
map<ll,string> hashash[1005];

int previous[maxn];
string match[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    init_inverse();
    cin >> n >> s;
    cin >> m;
    for (int i = 0; i < m; i++) {
        string ss; cin >> ss;
        string lower = ss;
        for (char& c: lower) {
            c = tolower(c);
        }
        actual[lower] = ss;
        words[lower.size()].push_back(lower);
        Hash h = Hash(lower);
        //cout << lower << ": " << h.gethash() << '\n';
        hashash[lower.size()][h.gethash()] = lower;
    }
    memset(previous,-1,sizeof previous);
    previous[1] = 0;
    reverse(s.begin(),s.end());
    Hash hs = Hash(s);
    for (int i = 1; i <= n; i++) {
        if (previous[i] == -1) continue; //not possible
        for (auto& p: words) {
            int sz = p.first;
            //cout << sz << '\n';
            if (i+sz > n + 1) continue;
            if (previous[i+sz] != -1) continue;
            //cout << sz << ": " << hs.sub(i,i+sz-1) << '\n';
            if (hashash[sz].count(hs.sub(i,i+sz-1))) {
                //cout << i << ' ' << sz << ": " << hs.sub(i,i+sz-1) << '\n';
                previous[i+sz] = i;
                match[i+sz] = hashash[sz][hs.sub(i,i+sz-1)];            
            }
        }
    }
    assert(previous[n+1] != -1);
    vector<string> ans;
    int curr = n + 1;
    while (curr != 0) {
        //assert(match[curr] != "");
        ans.push_back(match[curr]);
        curr = previous[curr];
    }
    for (auto p: ans) {
        cout << actual[p] << ' ';
    }
    cout << '\n';
}

