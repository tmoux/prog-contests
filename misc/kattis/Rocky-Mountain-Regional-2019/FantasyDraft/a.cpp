#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 65;
vector<string> pref[maxn];
int n, k;
map<string,int> mp;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        int qi; cin >> qi;
        while (q--) {
            string s; cin >> s;
            pref[i].push_back(s);
        }
    }
    int p; cin >> p;
    for (int i = 0; i < p; i++) {
        string s; cin >> s;
        mp[s] = i+1;
    }
    for (int i = 1; i <= n; i++) {

    }
}

