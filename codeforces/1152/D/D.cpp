#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n;
const int M = 1e9+7;
int tab[1005][1005];
int sum[1005];

int madd(int a, int b) {
    return (a+b) % M;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= i; j++) {
            if (j == 0) tab[j][i] = 1;    
            else tab[j][i] = madd(tab[j-1][i],tab[j][i-1]);
        }
    }
    int ans = 0;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            if ((i+j) % 2 == 1) {
                ans = madd(ans,tab[i][j]);
            }
        }
    }
    cout << ans << '\n';

    return 0;
}
