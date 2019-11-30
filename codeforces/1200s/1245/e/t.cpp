#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    int grid[10][10];
    for (int i = 0; i != 10; ++i)
        for (int j = 0; j != 10; ++j)
            cin >> grid[i][j];
    
    int flat[10][10];
    for (int i = 0; i != 10; ++i)
        for (int j = 0; j != 10; ++j)
                flat[i][j] = (9 - i) * 10 + ((i & 1) ? j : 9 - j);
    
    int d = 1;
    int x = 9;
    int y = 0;
    int arr[100];
    for (int i = 0; i != 100; ++i)
    {
        arr[i] = flat[x - grid[x][y]][y];
        
        if (y + d == -1 || y + d == 10)
        {
            d *= -1;
            x--;
        }
        else
            y += d;
    }
    
    double dp[100];
    dp[99] = 0;
    for (int i = 98; i >= 0; --i)
    {
        dp[i] = 1;
        
        int c = 6;
        for (int r = 1; r <= 6; ++r)
        {
            if (i + r >= 100)
                continue;
            dp[i] += min(dp[i + r], dp[arr[i + r]]) / 6;
            c--;
        }
        
        dp[i] = 6 * dp[i] / (6 - c);
        cout << i << ": " << dp[i] << '\n';
    }
    
    cout << setprecision(10) << fixed << dp[0] << '\n';
    
    return 0;
}
