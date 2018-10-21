#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    int nn = n*(n+1)/2;
    for (int i = 2; i <= n; i++) {
        if (nn % i == 0) {
            cout << "Yes" << '\n';
            cout << 1 << ' ' << i << '\n';
            cout << n-1 << ' ';
            for (int j = 1; j <= n; j++) {
                if (j != i) cout << j << ' ';
            }
            cout << '\n';
            return 0;
        }
    }
    cout << "No\n";

    return 0;
}

