#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    int total = 0;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        total += a[i];
    }
    int majority = total/2+1;
    int ours = a[0];
    vector<int> ans = {1};
    for (int i = 1; i < n; i++) {
        if (a[i]*2 <= a[0]) {
            ours += a[i];
            ans.push_back(i+1);
        }
    }
    if (ours >= majority) {
        cout << ans.size() << '\n';
        for (int i: ans) {
            cout << i << ' ';
        }
        cout << '\n';
    }
    else {
        cout << 0 << '\n';
    }
}

