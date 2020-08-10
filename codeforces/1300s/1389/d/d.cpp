#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n;
        ll k; 
        cin >> n >> k;
        ll l1, r1, l2, r2; cin >> l1 >> r1 >> l2 >> r2;
        if (l1 > l2) {
            swap(l1,l2);
            swap(r1,r2);
        }
        ll len = max(r1,r2)-l1;
        ll up_cost = max(0LL,l2-r1);
        ll already = max(0LL,min(r1,r2)-l2);
        //cout << len << ' ' << up_cost << ' ' << already << '\n';
        ll ans = 2e9+9;
        for (int i = 1; i <= n; i++) {
            ll need = k-i*already;
            if (need <= 0) {
                ans = 0;
            }
            else {
                ll tr = up_cost*i;
                if (need <= i*(len-already)) {
                    tr += need;
                }
                else {
                    tr += i*(len-already);
                    need -= i*(len-already);
                    tr += need*2;
                }
                ans = min(ans,tr);
            }
        }
        cout << ans << '\n';
    }
}
