#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, s; cin >> n >> s;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    if (a[0] == 0) {
        cout << "NO\n";
        return 0;
    }
    if (a[s-1] == 1) {
        cout << "YES\n";
    }
    else {
        for (int i = s; i < n; i++) {
            if (a[i] == 1 && b[i] == 1 && b[s-1] == 1) {
                cout << "YES\n";
                return 0;
            }
        }
        cout << "NO\n";
    }
}

