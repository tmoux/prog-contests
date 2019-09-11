#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n, m;
const int maxn = 1e6+6;

int dx[] = {0,1,0,-1};
int dy[] = {1,0,-1,0};

bool valid(int i, int j) {
    return 0 <= i && i < n && 0 <= j && j < m;
}

vector<vector<bool>> canReach;
vector<vector<char>> grid;
vector<vector<bool>> ac;


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        vector<char> v;
        for (int j = 0; j < m; j++) {
            char c; cin >> c;
            v.push_back(c);
        }
        grid.push_back(v);
        canReach.push_back(vector<bool>(m,false));
    }

    for (int i = n-1; i >= 0; i--) {
        for (int j = m-1; j >= 0; j--) {
            if (i == n-1 && j == m-1) canReach[i][j] = true;
            else if (grid[i][j] == '#') continue;
            else {
                canReach[i][j] = false;
                if (i < n-1) canReach[i][j] = canReach[i][j] | canReach[i+1][j];
                if (j < m-1) canReach[i][j] = canReach[i][j] | canReach[i][j+1];
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i == 0 && j == 0) continue;
            else if (grid[i][j] == '#') continue;
            else {
                bool poss = false;
                if (i > 0) poss = poss | canReach[i-1][j];
                if (j > 0) poss = poss | canReach[i][j-1];
                canReach[i][j] = (canReach[i][j] & poss);
            }
        }
    }

    /*
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << canReach[i][j] << ' ';
        }
        cout << '\n';
    }
    */

    if (!canReach[0][0]) {
        cout << 0 << '\n';
    }
    else {
        vector<int> num(n+m+5,0);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (i == 0 && j == 0) continue;
                if (i == n-1 && j == m-1) continue;
                if (canReach[i][j]) num[i+j]++;
            }
        }
        for (int i = 1; i < n+m-2; i++) {
            if (num[i] == 1) { //chokepoint
                cout << 1 << '\n';
                return 0;
            }
        }
        cout << 2 << '\n';        
        return 0;
    }
}

