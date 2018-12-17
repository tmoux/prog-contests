#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
    int xi; cin >> xi;
    int r = 0;
    while (true) {
        if (xi <= 7) {
            r++;
            break;
        }
        else {
            xi -= 2;
            r++;
        }
    }
    cout << r << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();

    return 0;
}

