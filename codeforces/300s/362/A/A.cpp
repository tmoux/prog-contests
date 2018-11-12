#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

char grid[8][8];
int dx[] = {-2,2,-2,2};
int dy[] = {2,-2,-2,2};

void fill1(int x, int y) {
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx < 0 || y < 0 || x >= 8 || y >= 8) continue;
        if (grid[nx][ny] == '.') {
            grid[nx][ny] = '0';
            fill1(nx,ny);
        }
    }
}

void fill2(int x, int y, bool& poss) {
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx < 0 || ny < 0 || nx >= 8 || ny >= 8) continue;
        if (grid[nx][ny] == '0') poss = true;
        if (grid[nx][ny] == '.') {
            grid[nx][ny] = '1';
            fill2(nx,ny,poss);
        }
    }
}
void solve() {
    pair<int,int> a[2];
    int c = 0;
    for (int i = 0; i < 8; i++) {
        string s; cin >> s;
        for (int j = 0; j < 8; j++) {
            grid[i][j] = s[j];
            if (grid[i][j] == 'K') {
                grid[i][j] = c+'0';
                a[c++] = {i,j};
            }
        }
    }
    int d1 = abs(a[0].first-a[1].first);
    int d2 = abs(a[0].second-a[1].second);
    if (d1 % 4 == 0 && d2 % 4 == 0 && (d1/2) % 2 == (d2/2) % 2) {
        cout << "YES" << '\n';    
    }
    else {
        cout << "NO\n";
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t; while (t--) solve();
    return 0;
}

