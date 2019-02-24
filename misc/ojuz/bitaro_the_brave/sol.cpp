#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 5005;
char grid[maxn][maxn];
int ocnt[maxn][maxn], icnt[maxn][maxn];
int H, W;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> H >> W;
    for (int i = 1; i <= H; i++) {
        for (int j = 1; j <= W; j++) {
            cin >> grid[i][j];
        }
    }
    for (int i = 1; i <= H; i++) {
        for (int j = W; j >= 1; j--) {
            ocnt[i][j] = ocnt[i][j+1];
            if (grid[i][j] == 'O') ocnt[i][j]++;
        }
    }
    for (int j = 1; j <= W; j++) {
        for (int i = H; i >= 1; i--) {
            icnt[i][j] = icnt[i+1][j];
            if (grid[i][j] == 'I') icnt[i][j]++;
        }
    }
    ll ans = 0;
    for (int i = 1; i <= H; i++) {
        for (int j = 1; j <= W; j++) {
            if (grid[i][j] != 'J') continue;
            ans += 1LL * ocnt[i][j] * icnt[i][j];
        }
    }
    cout << ans << '\n';
}

