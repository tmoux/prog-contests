#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1005;
bool grid[maxn][maxn], copp[maxn][maxn];
int n, m;

struct Star { int x, y, sz; };
vector<Star> rows[maxn], cols[maxn];
int colpre[maxn][maxn], rowpre[maxn][maxn];

int colsum(int c, int i, int j) {
    if (i > j) swap(i,j);
    return (i == 0 ? colpre[j][c] : colpre[j][c] - colpre[i-1][c]);
}
int rowsum(int r, int i, int j) {
    if (i > j) swap(i,j);
    return (i == 0 ? rowpre[r][j] : rowpre[r][j] - rowpre[r][i-1]);
}

bool checkRow(pair<int,int>& p, pair<int,int>& st, int sz) {
    if (0 <= p.first && p.first < n && 0 <= p.second && p.second < m) {
        return abs(rowsum(p.first,p.second,st.second)) == sz;
    }
    return false;
}

bool checkCol(pair<int,int>& p, pair<int,int>& st, int sz) {
    if (0 <= p.first && p.first < n && 0 <= p.second && p.second < m) {
        return abs(colsum(p.second,p.first,st.first)) == sz;
    }
    return false;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    vector<pair<int,int>> pts;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        for (int j = 0; j < m; j++) {
            grid[i][j] = s[j] == '*';    
            if (grid[i][j]) {
                pts.push_back({i,j});
            }
        }
    }
    //setup

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            rowpre[i][j] = grid[i][j];
            if (j != 0) rowpre[i][j] += rowpre[i][j-1];
        }
    }
    for (int j = 0; j < m; j++) {
        for (int i = 0; i < n; i++) {
            colpre[i][j] = grid[i][j];
            if (i != 0) colpre[i][j] += colpre[i-1][j];
        } 
    }

    //calc
    vector<Star> stars;
    for (int i = 1; i < n - 1; i++) {
        for (int j = 1; j < m - 1; j++) {
            if (!grid[i][j]) continue;
            int sz = 0;
            for (int k = 11; k >= 0; k--) {
                int nz = sz + (1 << k);
                pair<int,int> up = {i-nz,j}, down = {i+nz,j}, left = {i,j+nz}, right = {i,j-nz};
                pair<int,int> ca = {i,j};
                if (checkCol(up,ca,nz+1) && checkCol(down,ca,nz+1) && checkRow(left,ca,nz+1) && checkRow(right,ca,nz+1)) {
                    sz = nz;
                }
            }
            
            if (sz >= 1) {
                Star s = {i,j,sz};
                stars.push_back({i+1,j+1,sz});
                rows[i].push_back(s);
                cols[j].push_back(s);
                //cout << i+1 << ' ' << j+1 << ' ' << sz << '\n';
            }
        }
    }

    //check if possible
    for (auto p: pts) {
        //check that all are covered
        bool flag = false;
        for (Star s: rows[p.first]) {
            if (abs(s.y-p.second) <= s.sz) {
                flag = true;
                break;
            }
        }
        if (!flag) {
            for (Star s: cols[p.second]) {
                if (abs(s.x-p.first) <= s.sz) {
                    flag = true;
                    break;
                }
            }
        }
        if (!flag) {
            cout << -1 << '\n';
            return 0;
        }
    }

    //output
    cout << stars.size() << '\n';
    for (Star s: stars) {
        cout << s.x << ' ' << s.y << ' ' << s.sz << '\n';
    }

    return 0;
}
	

