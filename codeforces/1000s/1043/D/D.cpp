#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5, maxm = 12;
int a[maxm][maxn], n, m;
int reorder[maxn]; //reorder permutation
int maxreach[maxm][maxn];

int main()
{
    scanf("%d %d",&n,&m);
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%d",&a[i][j]);
        }
    }
    //reorder 1st permutation
    for (int j = 1; j <= n; j++) {
        reorder[a[1][j]] = j;    
    }
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            a[i][j] = reorder[a[i][j]];
        }
    }
    for (int j = 1; j <= m; j++) {
        for (int i = n; i >= 1; i--) {
            if (i == n || a[j][i+1] != a[j][i] + 1) {
                maxreach[j][a[j][i]] = 1;
            }
            else maxreach[j][a[j][i]] = maxreach[j][a[j][i+1]] + 1;
            //cout << j << ' ' << i << ' ' << a[j][i] << ": " << maxreach[j][a[j][i]] << '\n';
        }
    }
    ll res = 0;
    vector<int> mx(n+1,maxn);
    for (int i = 1; i <= n; i++) {
        int mr = maxn;
        for (int j = 1; j <= m; j++) {
            mr = min(mr,maxreach[j][i]);
        }
        res += mr;
    }
    cout << res << '\n';

    return 0;
}

