#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int N, a[105];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    ll ans = 0;
    for (int i = 1; i <= N; i++) {
        cin >> a[i];
        ans += a[i];
    }
    ll sub = 0;
    for (int x = N; x >= 1; x++) {
        ll cost = 0;
        for (int i = x; i <= N; i += x) {
            cost += a[i];
        }
        if (cost < 0) {
            for (int i = x; i <= N; i += x) {
                a[i] = 0;
            }
            sub += cost;
        }
    }
    cout << (ans-sub) << '\n';
}

