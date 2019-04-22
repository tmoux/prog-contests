#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        int ans = 0;
        vector<pair<int,int>> invls;
        invls.push_back({1,n});
        for (int a = 0; a < 9; a++) {
            vector<pair<int,int>> newInvls;
            for (pair<int,int> pa: invls) {
                if (pa.first == pa.second) {
                    newInvls.push_back(pa);
                }
                else {
                    int m = (pa.first+pa.second)/2;
                    newInvls.push_back({pa.first,m});
                    newInvls.push_back({m+1,pa.second});
                }
            }
            invls = newInvls;
            set<int> p, q;
            for (int i = 0; i < invls.size(); i++) {
                for (int j = invls[i].first; j <= invls[i].second; j++) {
                    if (i&1) q.insert(j);
                    else p.insert(j);
                }
            }
            if (!p.empty() && !q.empty()) {
                cout << p.size() << ' ' << q.size() << ' ';
                for (int i: p) {
                    cout << i << ' ';
                }
                for (int i: q) {
                    cout << i << ' ';
                }
                cout << endl;
                int r; cin >> r;
                if (r == -1) exit(0);
                ans = max(ans,r);
            }
        }
        cout << -1 << ' ' << ans << endl;
    }
}

