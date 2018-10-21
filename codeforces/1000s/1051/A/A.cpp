#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
    string s; cin >> s;
    map<char,int> mp;
    map<char,vector<int>> mp2;
    int idx = 0;
    for (char c: s) {
        if ('a' <= c && 'z' >= c) {
            mp['a']++;
            mp2['a'].push_back(idx);
        }
        else if ('A' <= c && 'Z' >= c) {
            mp['A']++;
            mp2['A'].push_back(idx);
        }
        else {
            mp['1']++;
            mp2['1'].push_back(idx);
        }
        idx++;
    }
    if (mp.size() == 3) {
        cout << s << '\n';
    }
    else if (mp.size() == 2) {
        vector<char> v = {'a','A','1'};
        for (char vi: v) {
            if (!mp.count(vi)) {
                for (char c: v) {
                    if (c != vi && mp[c] > 1) {
                        s[mp2[c].front()] = vi;    
                        cout << s << '\n';
                        return;
                    }
                }
            }
        }
    }
    else {
        int i = 0;
        vector<char> v = {'a','A','1'};
        for (char vi: v) {
            if (!mp.count(vi)) {
                s[i++] = vi;
            }
        }
        cout << s << '\n';
        return;
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();


    return 0;
}

