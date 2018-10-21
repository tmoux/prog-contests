#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

const int maxn = 50;
bool grid[maxn][maxn];
int H, W;

bool check(int i, int j) {
    pair<int,int> dd[] = {{-1,0},{1,0},{0,-1},{0,1}};
    for (int a = 0; a < 4; a++) {
        int x = i + dd[a].first;
        int y = j + dd[a].second;
        if (x >= 0 && x < H && y >= 0 && y < W) {
            if (grid[x][y]) return true;
        }
    }
    return false;
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    //read input
    cin >> H >> W;
    for (int i = 0; i < H; i++) {
        string s; cin >> s;
        for (int j = 0; j < W; j++) {
            grid[i][j] = (s[j] == '#');
        }
    }
    //check that each black square is valid
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (grid[i][j] && !check(i,j)) {
                cout << "No\n";
                return 0;
            }
        }
        
    }
    cout << "Yes\n";
    return 0;
}
	

