#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, k; cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<int> v;
    for (int i = 0; i < n; i++) {
        if (i == n-1 || a[i+1] != a[i]) {
            v.push_back(a[i]);
        }
    }
    vector<int> ans(k+1,v.size()-1);
    for (int i = 0; i < v.size(); i++) {
        if (i == 0 || i == v.size()-1) ans[v[i]]--;
        else {
            ans[v[i]] -= 2;
            if (v[i-1] != v[i+1]) ans[v[i]]++;
        }
    }
    int best = n;
    int ret = -1;
    for (int i = 1; i <= k; i++) {
        if (ans[i] < best) {
            best = ans[i];
            ret = i;
        }
    }
    cout << ret << '\n';
}

