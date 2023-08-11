#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int q; cin >> q;
    while (q--) {
        int n; cin >> n;
        vector<int> a(4*n);
        for (int i = 0; i < 4*n; i++) {
            cin >> a[i];
        }
        sort(a.begin(),a.end());
        vector<int> pairs;
        for (int i = 0; i < a.size()-1; i++) {
            if (a[i] != a[i+1]) {
                continue;
            }
            else {
                pairs.push_back(a[i]);
                i++;
            }
        }
        if (pairs.size() != 2*n) {
            cout << "NO\n";
        }
        else {
            set<int> areas;
            for (int l = 0, r = pairs.size()-1; l < r; l++,r--) {
                areas.insert(pairs[l]*pairs[r]);
            }
            cout << (areas.size() > 1 ? "NO" : "YES") << '\n';
        }
    }

}

