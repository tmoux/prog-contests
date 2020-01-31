#include <bits/stdc++.h>
using namespace std;
using ll = long long;

bool isv(char c) {
    return c == 'a' || c == 'e' || c == 'o' || c == 'i' || c == 'u' || c == 'y' || c == 'w';
}

int n;
int d[1000006];
int cnt[30][30];
int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    freopen("consonant.in","r",stdin); freopen("consonant.out","w",stdout);
    string s; cin >> s;
    n = s.size();
    map<char,int> mp;
    int pt = 0;
    for (int i = 0; i < n; i++) {
        if (isv(s[i])) {
            d[i] = 29;
            continue;
        }
        if (!mp.count(s[i])) mp[s[i]] = pt++;
        d[i] = mp[s[i]];
        if (i > 0) cnt[d[i]][d[i-1]]++;
    }
    if (pt == 0) {
        cout << s << endl;
        return 0;
    }
    int ans = -1;
    int best_mask = 0;
    for (int mask = 0; mask < (1<<pt); mask++) {
        vector<bool> v(pt,false);
        for (int i = 0; i < pt; i++) {
            if (mask & (1<<i)) v[i] = true;
            else v[i] = false;
        }
        int tr = 0;
        for (int i = 0; i < pt; i++) {
            for (int j = 0; j < pt; j++) {
                if (v[i] ^ v[j]) {
                    tr += cnt[i][j];
                }
            }
        }
        if (ans < tr) {
            ans = tr;
            best_mask = mask;
        }
    }
    for (char c: s) {
        if (isv(c)) cout << (char)c;
        else {
            if (best_mask & (1<<mp[c])) cout << (char)toupper(c);
            else cout << (char)tolower(c);
        }
    }
    cout << '\n';
}

