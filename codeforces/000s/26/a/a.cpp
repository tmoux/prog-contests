#include <bits/stdc++.h>
using namespace std;
using ll = long long;

bool is(int x) {
    vector<int> fac;
    int cp = x;
    for (int i = 2; i*i <= cp; i++) {
        if (x % i == 0) {
            fac.push_back(i);
            while (x % i == 0) {
                x /= i;
            }
        }
    }
    if (x > 1) fac.push_back(x);
    return fac.size() == 2;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        cnt += is(i);
    }
    cout << cnt << '\n';
}

