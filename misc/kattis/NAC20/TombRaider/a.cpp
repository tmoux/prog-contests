#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 505;
int n, m;
char grid[maxn][maxn];
int C = 0;
vector<int> adj[maxn*maxn*2];
//[0,C-1] is Horiz, [C,2*C-1] is Vert
int id[maxn][maxn];
int dx[] = {-1,0,1,0};//up, right, down, left
int dy[] = {0,1,0,-1};

bool valid(int i, int j) {
    return 0 <= i && i < n && 0 <= j && j < m;
}

int color[maxn*maxn*2];
int cost[maxn*maxn*2];
vector<set<int>> ss[maxn*maxn*2];

int trav(int i, int j, int orig, int dir) {
    //cout << i << ' ' << j << endl;
    if (!valid(i,j)) return orig;
    if (grid[i][j] == '#') return -1;
    if (grid[i][j] == 'H' || grid[i][j] == 'V') {
        if (dir == 1 || dir == 3) {
            return id[i][j];
        }
        else {
            return id[i][j]+C;
        }
    }
    if (grid[i][j] == '\\') {
        if (dir == 0) dir = 3;
        else if (dir == 1) dir = 2;
        else if (dir == 2) dir = 1;
        else if (dir == 3) dir = 0;
    }
    else if (grid[i][j] == '/') {
        if (dir == 0) dir = 1;
        else if (dir == 1) dir = 0;
        else if (dir == 2) dir = 3;
        else if (dir == 3) dir = 2;
    }
    return trav(i+dx[dir],j+dy[dir],orig,dir);
}

void dfs(int i, int c, int pt) {
    if (i == -1) return;
    color[i] = c;
    ss[pt][c].insert(i);
    for (auto j: adj[i]) {
        if (color[j] == -1) { //same color
            dfs(j,c,pt);
        }
    }
    if (i < C) {
        for (auto j: adj[i+C]) {
            if (color[j] == -1) { //diff color
                dfs(j,c^1,pt);
            }
        }
        if (color[i+C] == -1)
            dfs(i+C,c^1,pt);
    }
    if (i >= C) {
        for (auto j: adj[i-C]) {
            if (color[j] == -1) { //diff color
                dfs(j,c^1,pt);
            }
        }
        if (color[i-C] == -1) 
            dfs(i-C,c^1,pt);
    }
}

bool good(set<int>& s) {
    for (auto i: s) {
        if (i < C && s.count(i+C)) return false;
        if (i >= C && s.count(i-C)) return false;
    }
    return true;
}

bool poss(set<int>& s) {
    for (auto i: s) {
        for (auto j: adj[i]) {
            if (!s.count(j)) return false;
        }
        if (i < C) {
            if (s.count(i+C)) return false;
            for (auto j: adj[i+C]) {
                if (s.count(j)) return false;
            }
        }
        if (i >= C) {
            if (s.count(i-C)) return false;
            for (auto j: adj[i-C]) {
                if (s.count(j)) return false;
            }
        }
    }
    return true;
}

int acc(set<int>& s) {
    int r = 0;
    for (auto i: s) {
        r += cost[i];
    }
    return r;
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == 'H' || grid[i][j] == 'V') {
                id[i][j] = C;
                C++;
            }
        }
    }
    //build graph
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 'H' || grid[i][j] == 'V') {
                //assign costs
                if (grid[i][j] == 'H') {
                    cost[id[i][j]+C] = 1;
                }
                else if (grid[i][j] == 'V') {
                    cost[id[i][j]] = 1;
                }
                //if (!(i == 0 && j == 2)) continue;

                adj[id[i][j]].push_back(trav(i+dx[1],j+dy[1],id[i][j],1));
                //printf("(%d, %d): right = %d\n",i,j,adj[id[i][j]].back());

                adj[id[i][j]].push_back(trav(i+dx[3],j+dy[3],id[i][j],3));
                //printf("(%d, %d): left = %d\n",i,j,adj[id[i][j]].back());

                adj[id[i][j]+C].push_back(trav(i+dx[0],j+dy[0],id[i][j]+C,0));
                //printf("(%d, %d): up = %d\n",i,j,adj[id[i][j]+C].back());

                adj[id[i][j]+C].push_back(trav(i+dx[2],j+dy[2],id[i][j]+C,2));
                //printf("(%d, %d): down = %d\n",i,j,adj[id[i][j]+C].back());
            }
        }
    }
    memset(color,-1,sizeof color);
    int pt = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (color[id[i][j]] == -1) {
                ss[pt] = {set<int>(),set<int>()};
                dfs(id[i][j],0,pt);
                pt++;
            }
        }
    }
    bool flag = true;
    int res = 0;
    for (int i = 0; i < pt; i++) {
        /*
        cout << i << ":\n";
        cout << "s0:\n";
        for (auto j: ss[i][0]) {
            cout << j << ' ';
        }
        cout << '\n';
        cout << "adj: \n";
        for (auto ii: ss[i][0]) {
            for (auto j: adj[ii]) {
                cout << j << ' ';
            }
        }
        cout << '\n';
        cout << "poss: " << poss(ss[i][0]) << endl;
        cout << "s1:\n";
        for (auto j: ss[i][1]) {
            cout << j << ' ';
        }
        cout << '\n';
        cout << "poss: " << poss(ss[i][1]) << endl;
        */
        if (!good(ss[i][0]) || !good(ss[i][1])) {
            flag = false;
        }
        if (!poss(ss[i][0]) && !poss(ss[i][1])) {
            flag = false;
        }
        else if (!poss(ss[i][0])) {
            res += acc(ss[i][1]);
        }
        else if (!poss(ss[i][1])) {
            res += acc(ss[i][0]);
        }
        else {
            res += min(acc(ss[i][0]),acc(ss[i][1]));
        }
    }
    cout << (flag ? res : -1) << endl;
}
