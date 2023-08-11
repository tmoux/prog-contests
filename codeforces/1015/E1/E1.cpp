#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 105;
bool grid[maxn][maxn], copp[maxn][maxn];
int n, m;

bool isValid(pair<int,int>& p) {
    if (0 <= p.first && p.first < n && 0 <= p.second && p.second < m) {
        return grid[p.first][p.second];
    }
    return false;
}

void mark(vector<pair<int,int>> vec) {
    for (auto p: vec) {
        copp[p.first][p.second] = true;
    }
}

struct Star { int x, y, sz; };

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        for (int j = 0; j < m; j++) {
            grid[i][j] = s[j] == '*';    
        }
    }

    vector<Star> stars;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!grid[i][j]) continue;
            for (int sz = 1; sz < min(n,m); sz++) {
                pair<int,int> up = {i-sz,j}, down = {i+sz,j}, left = {i,j+sz}, right = {i,j-sz};
                if (isValid(up) && isValid(down) && isValid(left) && isValid(right)) {
                    mark({up,down,left,right,{i,j}});
                }
                else {
                    if (sz > 1) {
                        stars.push_back({i+1,j+1,sz-1});
                    }
                    break;
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] ^ copp[i][j]) {
                cout << -1 << '\n';
                return 0;
            }
        }
    }
    //output
    cout << stars.size() << '\n';
    for (Star s: stars) {
        cout << s.x << ' ' << s.y << ' ' << s.sz << '\n';
    }
    return 0;
}
	

