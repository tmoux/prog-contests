#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    vector<int> res(n+1,2e9);
    vector<bool> good(n+1,true);
    int cnt = n;
    for (int i = n; i > n/2; i--) {
        for (int j = i+i; j <= n; j += i) {
            if (good[j]) {
                good[j] = false;
                cnt--;
            }
        }
    }
    for (int g = n/2; g >= 1; g--) {
        res[cnt] = g;
        for (int j = g+g; j <= n; j += g) {
            if (good[j]) {
                good[j] = false;
                cnt--;
            }
        }
    }
    for (int i = n-1; i >= 1; i--) {
        res[i] = min(res[i],res[i+1]);
    }
    for (int i = 2; i <= n; i++) {
        cout << res[i] << ' ';
    }
    cout << '\n';
}
