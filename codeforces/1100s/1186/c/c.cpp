#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e6+6;
int n, m;
string a, b;

int compute(string a, string b) {
    assert(a.size() == b.size());
    int ans = 0;
    for (int i = 0; i < a.size(); i++) {
        if (a[i] != b[i]) ans++;
    }
    ans %= 2;
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> a >> b;
    n = a.size();
    m = b.size();

    int numChange = 0;
    for (int i = 0; i < m; i++) {
        if (i+1 < n && a[i] != a[i+1]) numChange++;
    }
    int curr = compute(a.substr(0,m),b);
    int ans = 0;
    if (curr == 0) ans++;
    for (int i = 1; i+m-1 < n; i++) {
        if (numChange % 2 == 1) curr ^= 1;
        if (curr == 0) ans++;
        //cout << i << ": " << numChange << ' ' << ans << '\n';

        if (a[i] != a[i-1]) numChange--;
        if (i+m < n && a[i+m-1] != a[i+m]) numChange++;
        
    }
    cout << ans << '\n';

}

