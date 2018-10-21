#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

inline int lg(int x) { 
    return x <= 1 ? 0 : 31 - __builtin_clz(x);
}
const int maxn = 1e5+5, maxm = 6, maxz = 18;
int n, m, k, A[maxm][maxn];
int mx[maxm][maxz][maxn];

int maxq(int j, int l, int r) {
    int d = lg(r-l+1);
    //cout << j << ' ' << l << ' '  << r << ' ' << d << ": ";
    //cout << max(mx[j][d][l],mx[j][d][r+1-(1<<d)]) << '\n';
    return max(mx[j][d][l],mx[j][d][r+1-(1<<d)]);
}

bool check(int l, int r) {
    int tot = 0;
    for (int j = 0; j < m; j++) {
        tot += maxq(j,l,r);
    }
    return tot <= k;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> A[j][i];
            mx[j][0][i] = A[j][i];
        }
    }
    //sparse table precomp
    for (int j = 0; j < m; j++) {
        for (int z = 1; z < lg(n+5) + 1; z++) {
            for (int i = 0; i < n; i++) {
                if (i + (1 << (z-1)) <= n-1) {
                    mx[j][z][i] = max(mx[j][z-1][i],mx[j][z-1][i+(1<<(z-1))]);
                    //cout << j << ' ' << i << " to " << (i+(1<<z)-1) << ' ' << mx[j][z][i] << '\n';
                }
            }
        }
    }

    int maxans = 0;
    vector<int> ans(m);
    for (int i = 0; i < n; i++) {
        int far = i;
        for (int z = lg(n+5); z >= 0; z--) {
            int nx = far + (1 << z);
            if (nx > n - 1) continue;
            if (check(i,nx)) {
                far = nx;
            }
        }
        if (check(i,far) && far-i+1 > maxans) {
            maxans = far-i+1;
            for (int j = 0; j < m; j++) {
                ans[j] = maxq(j,i,far);
            }
        }
    }
    //output
    for (int j = 0; j < m; j++) {
        cout << ans[j] << ' ';
    }
    //cout << maxq(0,0,99999) << '\n';

    return 0;
}

