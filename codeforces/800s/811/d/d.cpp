#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 105;
char grid[maxn][maxn];
int n, m;
pair<int,int> target;

bool horizSwap = false, vertSwap = false;

pair<int,int> moveLeft() {
    cout << (horizSwap?'L':'R') << endl;
    int x, y; cin >> x >> y;
    if (x == -1) exit(0);
    return {x,y};
}

pair<int,int> moveRight() {
    cout << (horizSwap?'R':'L') << endl;
    int x, y; cin >> x >> y;
    if (x == -1) exit(0);
    return {x,y};
}

pair<int,int> moveUp() {
    cout << (vertSwap?'U':'D') << endl;
    int x, y; cin >> x >> y;
    if (x == -1) exit(0);
    return {x,y};
}

pair<int,int> moveDown() {
    cout << (vertSwap?'D':'U') << endl;
    int x, y; cin >> x >> y;
    if (x == -1) exit(0);
    return {x,y};
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == 'F') {
                target = {i,j};
            }
        }
    }
    if (target == make_pair(1,1)) {
        return 0;
    }
    pair<int,int> curr = {1,1};
    if (grid[1][2] == '.') {
        pair<int,int> nc = moveRight();
        if (curr == nc) {
            //need to swap
            horizSwap = true;
        }
        curr = nc;
    }
    if (curr != make_pair(1,1)) moveLeft();
    if (grid[2][1] == '.') {
        pair<int,int> nc = moveDown();
        if (curr == nc) {
            //need to swap
            vertSwap = true;
        }
    }
    
}
