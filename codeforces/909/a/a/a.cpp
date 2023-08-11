#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    string a, b; cin >> a >> b;
    string res;
    res += a[0];
    int pt = 1;
    while (pt < a.size() && a[pt] < b[0]) {
        res += a[pt];
        pt++;
    }
    res += b[0];
    cout << res << '\n';
}

