#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int T; cin >> T;
    while (T--) {
        string x, y;
        cin >> x >> y;
        int cnt = 0;
        for (int i = y.size() - 1; i >= 0; i--) {
            if (y[i] == '0') cnt++;
            else break;
        }
        cnt++;
        //cout << "cnt = " << cnt << '\n';
        int ans = 0;
        for (int i = x.size()-cnt; i >= 0; i--) {
            if (x[i] == '0') ans++;
            else break;
        }
        cout << ans << '\n';
    }

}

