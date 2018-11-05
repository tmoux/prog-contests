#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 105;
bool g[maxn][maxn];

void f(int x, int y, int d, int e, bool s) {
    for (int i = x; i < x+d; i++) {
        for (int j = y; j < y+e; j++) {
            g[i][j] = s;
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int w, h, k; cin >> w >> h >> k;
    for (int i = 0; i < k; i++) {
        f(2*i,2*i,h-4*i,w-4*i,1);
        f(2*i+1,2*i+1,h-4*i-2,w-4*i-2,0);
    }
    int ans = 0;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            ans += g[i][j];
        }
    }
    cout << ans << '\n';

    return 0;
}

