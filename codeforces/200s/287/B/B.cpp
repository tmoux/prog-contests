#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    ll n, k; cin >> n >> k;
    ll sum = k;
    if (n == 1) {
        cout << 0 << '\n';
        return 0;
    }
    if (sum >= n) {
        cout << 1 << '\n';
        return 0;
    }
    for (int i = k - 1; i >= 2; i--) {
        sum += i - 1;
        if (sum >= n) {
            cout << k - i + 1;
            return 0;
        }
    }
    cout << -1 << '\n';

    return 0;
}
	

