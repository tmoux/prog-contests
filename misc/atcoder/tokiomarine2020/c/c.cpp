#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, k; cin >> n >> k;
    vector<int> a(n,0), b(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int iter = 0; iter < min(500,k); iter++) {
        vector<int> pfx(n+1,0);
        for (int i = 0; i < n; i++) {
            pfx[max(0,i-a[i])]++;
            pfx[min(n,i+a[i]+1)]--;
        }
        for (int i = 1; i <= n; i++) {
            pfx[i] += pfx[i-1];
        }
        a = pfx;
    }
    for (int i = 0; i < n; i++) {
        cout << a[i] << ' ';
    }
    cout << '\n';
}
