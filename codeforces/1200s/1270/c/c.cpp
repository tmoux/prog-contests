#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n;
int a[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        cin >> n;
        ll sum = 0, xo = 0;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            sum += a[i];
            xo ^= a[i];
        }
        if (sum == 2*xo) {
            cout << "0\n\n";
            continue;
        }
        ll target = (1LL<<60);
        ll a1 = (target/2) ^ xo;
        assert(target == (xo^a1)*2);
        ll a2 = (target-sum-a1)/2;
        ll a3 = (target-sum-a1)/2;
        //cout << sum+a1+a2+a3 << ' ' << 2*(xo^a1^a2^a3);
        //assert(sum+a1+a2+a3 == 2*(xo^a1^a2^a3));
        cout << 3 << '\n';
        cout << a1 << ' ' << a2 << ' ' << a3 << '\n';
        //cout << sum+a1+a2+a3 << ' ' << 2*(xo^a1^a2^a3) << '\n';
    }
}

