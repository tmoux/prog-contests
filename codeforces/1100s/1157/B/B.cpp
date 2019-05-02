#include <bits/stdc++.h>
using namespace std;
using ll = long long;


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        char c; cin >> c;
        a[i] = c-'0';
    }
    vector<int> f(10);
    for (int i = 1; i <= 9; i++) {
        cin >> f[i];
    }
    int mode = 0;
    for (int i = 0; i < n; i++) {
        if (mode == 2) {

        }
        else {
            if (f[a[i]] > a[i] || (mode == 1 && f[a[i]] == a[i])) {
                a[i] = f[a[i]];
                if (mode == 0) mode = 1;
            }
            else {
                if (mode == 1) mode = 2;
            }
        }
        cout << a[i];
    }
    cout << '\n';

    return 0;
}

