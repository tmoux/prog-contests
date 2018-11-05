#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    cout << n << ' ' << 1 << '\n';
    for (int i = 2; i <= n; i++) {
        cout << 1 << ' ' << i << '\n';
    }

    return 0;
}

