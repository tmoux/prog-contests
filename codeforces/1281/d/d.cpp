#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 65;
char grid[maxn][maxn];
int s[maxn][maxn];
int t, r, c;

int sum(int r1, int c1, int r2, int c2) {
    if (r1 > r2 || c1 > c2) return 0;
    return s[r2][c2] - s[r1-1][c2] - s[r2][c1-1] + s[r1-1][c1-1];
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> t;
    while (t--) {
        cin >> r >> c;
        int tot = 0;
        bool hasA = false;
        for (int i = 0; i <= r; i++) {
            for (int j = 0; j <= c; j++) {
                s[i][j] = 0;
            }
        }
        for (int i = 1; i <= r; i++) {
            for (int j = 1; j <= c; j++) {
                cin >> grid[i][j];
                if (grid[i][j] == 'A') hasA = true;
                else tot++;
                s[i][j] = grid[i][j] == 'A' ? 0 : 1;
            }
        }
        for (int i = 1; i <= r; i++) {
            for (int j = 1; j <= c; j++) {
                s[i][j] = s[i][j] + s[i-1][j] + s[i][j-1] - s[i-1][j-1];
            }
        }
        if (!hasA) {
            cout << "MORTAL\n";
            continue;
        }
        if (sum(1,1,r,c) == 0) {
            cout << 0 << '\n';
            continue;
        }
        int ans = 4;
        for (int i = 1; i <= r; i++) {
            int tr = sum(1,1,i,c);
            if (tr == 0) ans = min(ans,1);
            tr = sum(i,1,r,c);
            if (tr == 0) ans = min(ans,1);
        }
        for (int j = 1; j <= c; j++) {
            int tr = sum(1,1,r,j);
            if (tr == 0) ans = min(ans,1);
            tr = sum(1,j,r,c);
            if (tr == 0) ans = min(ans,1);
        }
        //corners
        for (int i = 1; i <= r; i++) {
            for (int j = 1; j <= c; j++) {
                if (grid[i][j] != 'A') continue;
                int tr = sum(1,1,i,j);
                tr = max(tr,sum(1,j,i,c));
                tr = max(tr,sum(i,1,r,j));
                tr = max(tr,sum(i,j,r,c));
                tr = tot - tr;
                if (tr == 0) ans = min(ans,2);
            }
        }
        for (int i = 1; i <= r; i++) {
            int tr = sum(i,1,i,c);
            if (tr == 0) ans = min(ans,2);
        }
        for (int j = 1; j <= c; j++) {
            int tr = sum(1,j,r,j);
            if (tr == 0) ans = min(ans,2);
        }
        //3 case
        for (int i = 1; i <= r; i++) {
            for (int j = 1; j <= c; j++) {
                if (grid[i][j] != 'A') continue;
                int tr = sum(1,1,i-1,c);
                tr = min(tr,sum(i+1,1,r,c));
                tr = min(tr,sum(1,1,r,j-1));
                tr = min(tr,sum(1,j+1,r,c));
                if (tr == 0) ans = min(ans,3);
            }
        }
        cout << ans << '\n';
    }
}

