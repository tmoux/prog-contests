#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 105;
int r, c, k;
char grid[maxn][maxn];
char ans[maxn][maxn];

string mp = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        cin >> r >> c >> k;
        int cnt = 0;
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                cin >> grid[i][j];
                if (grid[i][j] == 'R') cnt++;
            }
        }
        int target = cnt/k;
        int extra = cnt % k;
        int num = 0, cur = 0;
        for (int i = 0; i < r; i++) {
            if (i % 2 == 0) for (int j = 0; j < c; j++) {
                ans[i][j] = mp[min(k-1,num)];
                if (grid[i][j]=='R') cur++;
                if ((num < extra && cur == target+1) ||
                    (num >= extra && cur == target)) {
                    num++;
                    cur = 0;
                }
            }

            if (i % 2 == 1) for (int j = c-1; j >= 0; j--) {
                ans[i][j] = mp[min(k-1,num)];
                if (grid[i][j]=='R') cur++;
                if ((num < extra && cur == target+1) ||
                    (num >= extra && cur == target)) {
                    num++;
                    cur = 0;
                }
            }
        }
        //output
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                cout << ans[i][j];
            }
            cout << '\n';
        }
    }
}

