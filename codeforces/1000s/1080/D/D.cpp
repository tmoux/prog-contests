#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ll;

bool poss(ll n, ll k) {
    if (k == 0) return true;
    unsigned long long prev = 0;
    for (int i = 1; i <= n; i++) {
        prev = 1 + 4*prev;
        if (prev >= k) return true;
    }
    return false;
}

void solve() {
    ll n, k; cin >> n >> k;
    if (!poss(n,k)) {
        cout << "NO\n";
        return;
    }
    if (n==2&&k==3) {
        cout << "NO\n";
        return;
    }
    if (poss(n-1,k-1)) {
        cout << "YES" << ' ' << n-1 << '\n';
        return;
    }
    ll add = 1;
    ll prev = 1, curr;
    for (int i = n-1; i >= 0; i--) {
        add = add*2+1;
        curr = prev + add;   
        //cout << curr << '\n';
        if (curr > k) {
            cout << "YES" << ' ' << i << '\n';
            return;
        }
        prev = curr;
    }
    cout << "YES" << ' ' << 0 << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t; while (t--) solve();

    return 0;
}

