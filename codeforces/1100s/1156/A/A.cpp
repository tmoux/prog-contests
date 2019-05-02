#include <bits/stdc++.h>
using namespace std;
using ll = long long;


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    int prev; cin >> prev;
    int ans = 0;
    for (int i = 0; i < n - 1; i++) {
        int ai; cin >> ai;
        //cout << prev << ' ' << ai << '\n';
        if (prev == ai) {
            cout << "Infinite" << '\n';
            return 0;
        }
        else if (ai == 1) {
            if (prev == 2) ans += 3;
            else ans += 4;
        }
        else if (ai == 2) {
            if (ai == 1) ans += 3;
            else {
                cout << "Infinite\n";
                return 0;
            }
        }
        else {
            if (prev == 1) ans += 4;
            else {
                cout << "Infinite\n";
                return 0;
            }
        }
        prev = ai;
    }
    cout << "Finite\n";
    cout << ans << '\n';

    return 0;
}

