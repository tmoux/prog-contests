#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int q; cin >> q;
    while (q--) {
        int n; cin >> n;
        map<int,int> mp;
        for (int i = 0; i < n; i++) {
            int ai; cin >> ai;
            mp[ai]++;
        }
        bool poss = false;
        for (int i = 0; i < 50; i++) {
            if (mp.count(2048)) {
                poss = true;
                break;
            }
            if (mp.empty()) break;
            auto p = *mp.begin();
            mp.erase(mp.begin());
            if (p.second/2 > 0) mp[p.first*2] += p.second/2;
        }
        cout << (poss ? "YES" : "NO") << '\n';
    }

}

