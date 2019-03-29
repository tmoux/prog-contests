#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int calc(const string& s) {
    int dmg = 1;
    int res = 0;
    for (char c: s) {
        if (c == 'C') dmg *= 2;
        else res += dmg;
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    for (int qq = 1; qq <= t; qq++) {
        cout << "Case #" << qq << ": ";
        int D; cin >> D;
        string P; cin >> P;
        int ans = 0;
        while (calc(P) > D) {
            //find first "CS" to switch
            bool found = false;
            for (int i = P.size() - 1; i >= 1; i--) {
                if (P[i-1] == 'C' && P[i] == 'S') {
                    found = true;
                    swap(P[i-1],P[i]);
                    ans++;
                    break;
                }
            }
            if (!found) break;
        }
        if (calc(P) > D) {
            cout << "IMPOSSIBLE\n";
        }
        else {
            cout << ans << '\n';
        }
    }
}

