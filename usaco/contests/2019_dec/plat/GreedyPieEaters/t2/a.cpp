#include <bits/stdc++.h>
using namespace std;
using ll = long long;
//dp[i][j] = max(w[k]+dp[k+1][k+1])

const int maxn = 305;
int n, m;
struct Cow
{
    int w, l, r;
} cows[maxn*maxn];

int main() {
    //freopen("pieaters.in","r",stdin); freopen("pieaters.out","w",stdout);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> cows[i].w >> cows[i].l >> cows[i].r;    
    }
}
