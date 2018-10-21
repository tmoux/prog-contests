#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll A[200005];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; ll t; cin >> n >> t;
    for (int i = 1; i <= n; i++) {
        cin >> A[i];
        A[i] += A[i-1];
    }
    ll res = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            res += (A[j]-A[i-1]) < t;
        }
    }
    cout << res << '\n';

    return 0;
}

