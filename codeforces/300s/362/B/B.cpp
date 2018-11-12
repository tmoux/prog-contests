#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m; cin >> n >> m;
    if (m == 0) {
        cout << "YES" << '\n';
        return 0;
    }
    vector<int> a(m);
    for (int i = 0; i < m; i++) cin >> a[i];
    sort(a.begin(),a.end());
    if (*a.begin() == 1 || a.back() == n) {
        cout << "NO" << '\n';
    }
    else {
        for (int i = 0; i < m - 2; i++) {
            if (a[i+1] == a[i] + 1 && a[i+2] == a[i]+2) {
                cout << "NO\n";
                return 0;
            }
        }
        cout << "YES" << '\n';
    }

    return 0;
}

