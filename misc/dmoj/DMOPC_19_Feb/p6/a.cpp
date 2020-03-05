#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 405;
int N, M;
char grid[maxn][maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> grid[i][j];
        }
    }
    bool poss = false;
    if (N == 1) {
        cout << "YES\n";
        for (int j = 0; j < M; j++) {
            if (grid[0][j] == '?') grid[0][j] = '.';
            cout << grid[0][j];
        }
        cout << '\n';
        return 0;
    }
    if (N == 2) {
        for (int j = 0; j < M; j++) {
            if (grid[0][j] == '?') {
                poss = true;
                if (grid[1][j] == '?') {
                    grid[0][j] = '.';
                    grid[1][j] = 'X';
                }
                else {
                    grid[0][j] = grid[1][j] == '.' ? 'X' : '.';
                }
            }
            else if (grid[1][j] == '?') {
                poss = true;
                grid[1][j] = grid[0][j] == '.' ? 'X' : '.';
            }
            else {
                if (grid[0][j] != grid[1][j]) {
                    poss = true;
                }
            }
        }
        if (poss) {
            cout << "YES\n";
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) {
                    cout << grid[i][j];
                }
                cout << '\n';
            }
        }
        else {
            cout << "NO\n";
        }
        return 0;
    }
}

