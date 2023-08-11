#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n;

int ask(int x1, int y1, int x2, int y2) {
    printf("? %d %d %d %d\n",x1,y1,x2,y2);
    fflush(stdout);
    int ans; scanf("%d",&ans);
    assert(ans == 1 || ans == 0);
    return ans;
}

const int maxn = 55;
int grid[maxn][maxn];

bool found = false;
vector<pair<int,int>> st;
void dfs(int i, int j, int d, int curr) {
    if (found) return;
    curr ^= grid[i][j];
    st.push_back({i,j});
    if (d == 0 && curr == 0) {
        found = true;
        return;
    }
    if (d > 0) {
        if (i+1 <= n) dfs(i+1,j,d-1,curr);
        if (j+1 <= n) dfs(i,j+1,d-1,curr);
    }
    if (found) return;
    st.pop_back();
}

int main()
{
    cin >> n;
    grid[1][1] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if ((i+j) % 2 == 0) {
                if (i == 1 && j == 1) continue;
                else if (i == 2 && j == 2) {
                    grid[i][j] = ask(i-1,j-1,i,j) == 1 ? grid[i-1][j-1] : 1^grid[i-1][j-1];
                }
                else if (i <= 2) {
                    grid[i][j] = ask(i,j-2,i,j) == 1 ? grid[i][j-2] : 1^grid[i][j-2];
                }
                else {
                    grid[i][j] = ask(i-2,j,i,j) == 1 ? grid[i-2][j] : 1^grid[i-2][j];
                }
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if ((i+j) % 2 == 1) {
                if (i == 1 && j == 2) continue;
                else if (i == 2 && j == 1) continue;
                else if (i <= 2) {
                    grid[i][j] = ask(i,j-2,i,j) == 1 ? grid[i][j-2] : 1^grid[i][j-2];
                }
                else {
                    grid[i][j] = ask(i-2,j,i,j) == 1 ? grid[i-2][j] : 1^grid[i-2][j];
                }
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            dfs(i,j,3,0);
            if (found) break;
        }
    }
    assert(found && st.size() == 4);

    cout << "!\n";
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << grid[i][j];
        }
        cout << '\n';
    }
}

