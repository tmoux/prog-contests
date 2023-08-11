#include <iostream>
using namespace std;

const int maxn = 105;
bool grid[maxn][maxn];
int count[maxn][maxn];
int n, k;

void checkH(int row, int col) {
    bool poss = col+k-1 <= n;
    for (int i = 0; i+col <= n && i < k && poss; i++) {
        poss &= grid[row][col+i];
    }
    if (poss) {
        for (int i = 0; i+col <= n && i < k; i++) {
           count[row][col+i]++;
        }
    }
}

void checkV(int row, int col) {
    bool poss = row+k-1 <= n;
    for (int i = 0; i+row <= n && i < k && poss; i++) {
        poss &= grid[row+i][col];
    }
    if (poss) {
        for (int i = 0; i+row <= n && i < k; i++) {
           count[row+i][col]++;
        }
    }
}

int main()
{
    //input
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            char c; cin >> c;
            grid[i][j] = c == '.';
        }
    }

    int maxans = 0;
    pair<int,int> ansCell = {1,1};
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            checkH(i,j);
            checkV(i,j);
            if (count[i][j] > maxans) {
                maxans = count[i][j];
                ansCell = {i,j};
            }
        }
    }
    //output
    cout << ansCell.first << ' ' << ansCell.second << '\n';
}
