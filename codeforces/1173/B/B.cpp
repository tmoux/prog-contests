#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1005;
int x[maxn], y[maxn];
int grid[maxn][maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    if (n == 1) {
        cout << 1 << '\n';
        cout << "1 1\n";
        return 0;
    }
    int m = ((n+1)%2 == 0 ? (n+1)/2 : (n+1)/2+1);
    cout << m << '\n';
    for (int i = 1; i <= n; i++) {
        if (i <= n/2+1) {
            int xx = (i+1)/2;
            int yy = (i+1)/2;
            if (i%2 == 0) yy++;
            x[i] = xx;
            y[i] = yy;

            if (i <= n/2) {
                x[n+1-i] = m + 1 - xx;
                y[n+1-i] = m + 1 - yy;
            }
        }
        else if (n % 2 == 1 && i == n/2+1) {
                
        }
        else {
            /*
            int j = m + 1 - i/2;
            int xx = m + 1 - (j+1)/2;
            int yy = m + 1 - (j+1)/2;
            if (j % 2 == 0) yy--;
            x[i] = xx;
            y[i] = yy;
            */
        }
        grid[x[i]][y[i]] = i;
        //cout << x[i] << ' ' << y[i] << '\n';
    }

    for (int i = 1; i <= n; i++) {
        cout << x[i] << ' ' << y[i] << '\n';
    }

    /*
    cout << "\n\n";
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= m; j++) {
            cout << grid[i][j] << ' ';
        }
        cout << '\n';
    }
    */
}

