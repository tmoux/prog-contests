#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m; cin >> n >> m;
    while (m--) {
        int k; cin >> k;
        set<int> s1, s2;
        while (k--) {
            int v; cin >> v;
            if (v > 0) s1.insert(v);
            else s2.insert(v);
        }
        bool is = true;
        for (int p: s1) {
            if (s2.count(-p)) is = false;
        }
        if (is) {
            cout << "YES" << '\n';
            return 0;
        }
    }
    cout << "NO\n";

    return 0;
}

