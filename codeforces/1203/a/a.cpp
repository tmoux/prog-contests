#include <bits/stdc++.h>
using namespace std;
using ll = long long;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int q; cin >> q;
    while (q--) {
        int n; cin >> n;
        vector<int> p(2*n);
        for (int i = 0; i < n; i++) {
            cin >> p[i];
            p[i]--;
            p[i+n] = p[i];
        }
        bool inc = true;
        for (int i = 0; i < n; i++) {
            if (p[i+1] - p[i] == 1 || (p[i+1] == 0 && p[i] == n-1)) {
                continue;
            }
            else {
                inc = false;
                break;
            }
        }

        bool dec = true;
        for (int i = 0; i < n; i++) {
            if (p[i+1] - p[i] == -1 || (p[i] == 0 && p[i+1] == n-1)) {
                continue;
            }
            else {
                dec = false;
                break;
            }
        }
        cout << (inc || dec ? "YES" : "NO") << '\n';
    }

}

