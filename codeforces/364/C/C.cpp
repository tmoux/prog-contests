#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 4005;
int a;
string s;
int n;
int sums[maxn*9];
int tot = 0;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> a >> s;
    vector<int> pfx(s.size()+1);
    n = (int)(s.size());
    for (int i = 1; i < pfx.size(); i++) {
        pfx[i] = s[i-1] - '0';
        pfx[i] += pfx[i-1];
    }
    for (int i = 1; i < pfx.size(); i++) {
        for (int j = i; j < pfx.size(); j++) {
            int f = pfx[j] - pfx[i-1];
            sums[f]++;
            tot++;
        }
    }

    ll res = 0LL;
    if (a == 0) {
        for (int i = 1; i < pfx.size(); i++) {
            for (int j = i; j < pfx.size(); j++) {
                int f = pfx[j] - pfx[i-1];
                if (f != 0) res += sums[0];
                else res += tot;
            }
        }
        cout << res << '\n';
        return 0;
    }
    for (int i = 1; i < pfx.size(); i++) {
        for (int j = i; j < pfx.size(); j++) {
            int f = pfx[j] - pfx[i-1];
            if (f == 0 || f >= maxn*9) continue;
            if (a % f == 0 && a/f < maxn*9) {
                res += sums[a/f];
            }
        }
    }
    cout << res << '\n';

    return 0;
}

