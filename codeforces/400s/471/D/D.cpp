#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<int> z_function(vector<int> s) {
    int n = (int) s.size();
    vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r)
            z[i] = min (r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
    return z;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, w; cin >> n >> w;
    vector<int> a(n), b(w);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < w; i++) cin >> b[i];
    if (w == 1) {
        cout << n << '\n';
        return 0;
    }
    vector<int> spaces;
    for (int i = 0; i < w - 1; i++) {
        spaces.push_back(b[i+1]-b[i]);    
    }
    spaces.push_back((int)(2e9));
    for (int i = 0; i < n - 1; i++) {
        spaces.push_back(a[i+1]-a[i]);                        
    }
    auto z = z_function(spaces);
    int ans = 0;
    for (int i: z) {
        if (i == w-1) ans++;
    }
    cout << ans << '\n';

    return 0;
}

