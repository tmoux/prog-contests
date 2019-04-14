#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1005;
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
    Hash() {}
    Hash(const string& s) {
        len = s.size();
        str = s;
        reverse(str.begin(),str.end());
        prefix = new ll[maxn];
        prefix[0] = 0; //important!
        ll mult = 1;
        for (int i = 0; i < str.size(); i++) {
            prefix[i+1] = (prefix[i] + (ctoi(str[i])*mult)%M)%M;  
            mult = (mult*base)%M;
        }
    }

    ll sub(int l, int r) { //returns hash of [l,r] inclusive, 1-indexed
        return ((prefix[r]-prefix[l-1]+M)*inverse[l-1])%M;
    }

    pair<int,ll> LCS(const Hash& rhs) {
        if (str[0] != rhs.str[0]) return {0,0};
        if (len == rhs.len && rhs.len && prefix[len] == rhs.prefix[len]) return {len,prefix[len]};
        int l = min(len,rhs.len);
        int lo = 1, hi = l+1;
        while (lo + 1 < hi) {
            int mid = (lo+hi)/2;
            if (prefix[mid] == rhs.prefix[mid]) {
                lo = mid;    
            }
            else hi = mid;
        }
        return {lo,prefix[lo]};
        /*
        string res;
        for (int i = 0; i < lo; i++) {
            res += str[i];
        }
        reverse(res.begin(),res.end());
        return res;
        */
    }

    /*
    ~Hash() {
        delete[] prefix;
    }
    */
};
vector<Hash> hashes;

int N;

string LCS(string& a, string& b) {
    string ans = "";
    for (int i = 0; ; i++) {
        if ((int)a.size()-1-i < 0 || (int)b.size()-1-i < 0) break;
        if (a[a.size()-1-i] != b[b.size()-1-i]) break;
        ans = ans + a[a.size()-1-i];
    }
    return ans;
}

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
    int t; cin >> t;
    /*
    Hash a("abcdef"), b("aaaf");
    cout << a.LCS(b) << '\n';
    cout << b.LCS(a);
    return 0;
    */
    for (int qq = 1; qq <= t; qq++) {
        cin >> N;
        hashes.clear();
        vector<string> ss;
        for (int i = 0; i < N; i++) {
            string s; cin >> s;
            ss.push_back(s);
            hashes.emplace_back(Hash(s));
        }
        vector<bool> used(N);
        set<ll> uu;
        vector<pair<pair<int,ll>,pair<int,int>>> d;
        for (int i = 0; i < N; i++) {
            for (int j = i+1; j < N; j++) {
                pair<int,ll> lcs = hashes[i].LCS(hashes[j]);
                if (lcs.first == 0) continue;
                //cout << ss[i] << ' ' << ss[j] << ": " << lcs << endl;
                d.push_back({lcs,{i,j}});
            }
        }
        sort(d.begin(),d.end(),[](const auto& a, const auto& b) {
                return a.first.first > b.first.first;
                });
        int ans = 0;
        for (auto p: d) {
            if (used[p.second.first] || used[p.second.second]) {
                continue;
            }
            if (uu.count(p.first.second)) continue;
            ans += 2;
            used[p.second.first] = true;
            used[p.second.second] = true;
            uu.insert(p.first.second);
        }
        cout << "Case #" << qq << ": " << ans << '\n';
    }
}

