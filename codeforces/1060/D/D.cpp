#include <bits/stdc++.h>
using namespace std;
int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    vector<int> l(n), r(n);
    for (int i = 0; i < n; i++) cin >> l[i] >> r[i];
    sort(l.begin(),l.end()); sort(r.begin(),r.end());
    long long res = n;
    for (int i = 0; i < n; i++) res += max(l[i],r[i]);
    cout << res << '\n';
    return 0;
}

