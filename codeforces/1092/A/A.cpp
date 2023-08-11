#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n, k; cin >> n >> k;
        for (int i = 0; i < n; i++) {
            char c = 'a' + (i % k);
            cout << c;
        }
        cout << '\n';
    }

    return 0;
}

