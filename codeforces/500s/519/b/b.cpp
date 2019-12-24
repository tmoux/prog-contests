#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    vector<int> a(n), b(n-1), c(n-2);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n-1; i++) {
        cin >> b[i];
    }
    for (int i = 0; i < n-2; i++) {
        cin >> c[i];
    }
    sort(a.begin(),a.end());
    sort(b.begin(),b.end());
    sort(c.begin(),c.end());
    int c1 = a[n-1];
    for (int i = 0; i < n-1; i++) {
        if (a[i] != b[i]) {
            c1 = a[i];
            break;
        }
    }
    int c2 = b[n-2];
    for (int i = 0; i < n-2; i++) {
        if (b[i] != c[i]) {
            c2 = b[i];
            break;
        }
    }
    cout << c1 << '\n' << c2 << '\n';
}

