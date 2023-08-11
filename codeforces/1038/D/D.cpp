#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) cin >> v[i];
    if (n == 1) {
        cout << v[0] << '\n';
        return 0;
    }
    sort(v.begin(),v.end(),greater<int>());
    ll res = (ll)*v.begin() - v.back();
    for (int i = 1; i < n - 1; i++) res += abs(v[i]);
    cout << res << '\n';
    return 0;
}

