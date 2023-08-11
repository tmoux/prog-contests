#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int T;
    cin >> T;
    while (T--) {
        int n; cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        sort(a.begin(),a.end());
        int pt = n-1;
        bool done = false;
        for (int k = a[n-2]-1; k >= 0; k--) {
            if (n-2 >= k) {
                cout << k << '\n';
                done = true;
                break;
            }
        }
        if (!done) {
            cout << 0 << '\n';
        }
    }
}

