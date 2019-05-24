#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    for (int aa = 1; aa <= t; aa++) {
        cout << "Case #" << aa << ": ";
        int n; cin >> n;
        vector<pair<int,int>> ps;
        for (int i = 0; i < n; i++) {
            int a, b; cin >> a >> b;
            ps.push_back({a,b});
        }
        for (int i = 1; i <= 500; i++) {
            for (int j = 1; j <= 500; j++) {
                bool poss = true;
                for (int k = 0; k < ps.size() - 1; k++) {
                    int a = i*ps[k].first + j*ps[k].second;
                    int b = i*ps[k+1].first + j*ps[k+1].second;
                    if (a >= b) {
                        poss = false;
                        break;
                    }
                }
                if (poss) {
                    cout << i << ' ' << j << endl;
                    goto go;
                }
            }
        }
        cout << "IMPOSSIBLE\n";
        go:;
    }
}

