#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e6+6;
string s;
int n;
int label[maxn];

int bit[maxn];
void add(int i, int x) {
    for (; i <= n; i += i & (-i))
        bit[i] += x;
}

int sum(int i) {
    int r = 0;
    for (; i; i -= i & (-i)) {
        r += bit[i];
    }
    return r;
}

ll dist(string u, string v) {
    map<pair<char,int>,int> mp;    
    map<char,int> occ;
    for (int i = 0; i < u.size(); i++) {
        char c = u[i];
        occ[c]++;
        mp[make_pair(c,occ[c])] = i+1;
    }
    occ.clear();
    ll ret = 0;
    for (char c: v) {
        occ[c]++;
        int m = mp[make_pair(c,occ[c])];
        ret += sum(n) - sum(m);
        add(m,1);
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> s;
    n = s.size();
    map<char,int> mp;
    for (char c: s) {
        mp[c]++;
    }
    int odd = 0;
    for (auto p: mp) {
        if (p.second&1) odd++;
    }
    if (n % 2 == 0 && odd > 0) {
        cout << -1 << '\n';
        return 0;
    }
    else if (n % 2 == 1 && odd > 1) {
        cout << -1 << '\n';
        return 0;
    }
    for (auto p: mp) {
        int cnt = 0;
        if (p.second % 2 == 1) {
            for (int i = 0; i < n; i++) {
                if (s[i] == p.first) {
                    if (cnt < p.second/2) label[i] = 1;
                    else if (cnt == p.second/2) label[i] = 2;
                    else label[i] = 3;
                    cnt++;
                }
            }
        }
        else {
            for (int i = 0; i < n; i++) {
                if (s[i] == p.first) {
                    if (cnt < p.second/2) label[i] = 1;
                    else label[i] = 3;
                    cnt++;
                }
            }
        }
    }
    ll swaps = 0;
    vector<int> cnt(4,0);
    for (int i = 0; i < n; i++) {
        for (int j = label[i]+1; j <= 3; j++) {
            swaps += cnt[j];
        }
        cnt[label[i]]++;
    }
    string u, v;
    for (int i = 0; i < n; i++) {
        if (label[i] == 1) u += s[i];
        else if (label[i] == 3) v += s[i];
    }
    reverse(v.begin(),v.end());
    swaps += dist(u,v);
    cout << swaps << '\n';
}

