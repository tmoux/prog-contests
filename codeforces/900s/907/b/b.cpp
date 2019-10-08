#include <bits/stdc++.h>
using namespace std;
using ll = long long;

char g[9][9];
int x, y;

pair<int,int> which(int a, int b) {
    return {a/3,b/3};
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cin >> g[i][j];
        }
    }
    cin >> x >> y;
    x--; y--;
    int cnt = 0;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (i/3 == (x%3) && j/3 == (y%3) && g[i][j] == '.') {
                g[i][j] = '!';
                cnt++;
            }
        }
    }
    if (cnt == 0) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (g[i][j] == '.') {
                    g[i][j] = '!';
                }
            }
        }
    }
    //output
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cout << g[i][j];
            if (j == 2 || j == 5) cout << ' ';
        }
        cout << '\n';
        if (i == 2 || i == 5) cout << '\n';
    }
}

