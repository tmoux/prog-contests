#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    int cnt = 0;
    int h_min, h_max;
    cin >> h_min >> h_max;
    while (n--) {
        int ai; cin >> ai;
        if (h_min <= ai && ai <= h_max) {
            cnt++;
        }
    }
    cout << cnt << '\n';
}

