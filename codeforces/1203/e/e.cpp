#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a.begin(),a.end());
    set<int> ans;
    for (int i: a) {
        if (!ans.count(i-1) && i-1 > 0) ans.insert(i-1);
        else if (!ans.count(i)) ans.insert(i);
        else if (!ans.count(i+1)) ans.insert(i+1);
    }
    cout << ans.size() << '\n';
}

