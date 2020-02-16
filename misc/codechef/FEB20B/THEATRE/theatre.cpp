#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    int t; cin >> t;
    int tot = 0;
    while (t--) {
        int n; cin >> n;
        int ans = -2e9;
        vector<pair<int,int>> v;
        map<int,int> mp = {{12,0},{3,1},{6,2},{9,3}};
        for (int i = 0; i < n; i++) {
            char c;
            int t;
            cin >> c >> t;
            v.push_back({mp[t],c-'A'});
        }
        vector<int> p = {0,1,2,3}; //which show at time i
        do {
            vector<int> p2 = {25,50,75,100}; //which val at time i
            do {
                int tr = 0;
                vector<bool> seen(4,false);
                for (auto f: v) {
                    if (p[f.first] == f.second) {
                        seen[f.first] = true;
                        tr += p2[f.first];
                    }
                }
                for (int i = 0; i < 4; i++) {
                    if (!seen[i]) tr -= 100;
                }
                ans = max(ans,tr);
            } while (next_permutation(p2.begin(),p2.end()));
        } while (next_permutation(p.begin(),p.end()));
        cout << ans << '\n';
        tot += ans;
    }
    cout << tot << '\n';
}
