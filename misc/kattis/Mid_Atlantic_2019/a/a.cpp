#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int k; cin >> k;
    int ans = 1;
    vector<int> v;
    for (int i = 0; i < k; i++) {
        int ai; cin >> ai;
        v.push_back(ai);
    }
    for (int i = 0; i < k-1; i++) {
        if (v[i] > v[i+1]) ans++;
    }
    cout << ans << '\n';
}

