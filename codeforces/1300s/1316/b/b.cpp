#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        string s; cin >> s;
        vector<pair<string,int>> v;
        v.push_back({s,1});
        for (int k = 2; k < n; k++) {
            string rev = s.substr(0,k-1);
            reverse(rev.begin(),rev.end());
            if (!((k&1) ^ (n&1))) v.push_back({s.substr(k-1)+rev,k});
            else v.push_back({s.substr(k-1)+s.substr(0,k-1),k});
        }
        reverse(s.begin(),s.end());
        v.push_back({s,n});
        sort(v.begin(),v.end());
        cout << v[0].first << '\n' << v[0].second << '\n';
    }
}

