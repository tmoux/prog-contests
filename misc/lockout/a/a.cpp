#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    vector<int> a;
    for (int i = 0; i < n; i++) {
        int ai; cin >> ai;
        a.push_back(ai);
    }
    int ans = 0;
    for (int i = 1; i < n-1; i++) {
        if (a[i] < a[i-1] && a[i] < a[i+1])
            ans++;
        else if (a[i] > a[i-1] && a[i] > a[i+1]) ans++;
    }
    cout << ans << endl;
}

