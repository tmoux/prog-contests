#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int h, n; cin >> h >> n;
    int sum = 0;
    while (n--) {
        int ai; cin >> ai;
        sum += ai;
    }
    cout << (h <= sum ? "Yes" : "No") << endl;
}

