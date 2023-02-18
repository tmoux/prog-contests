#include <bits/stdc++.h>
using namespace std;
using ll = long long;
 
const int maxn = 4005;
int H, W;
char grid[maxn][maxn];
bool seen[maxn][maxn];
 
int dx[] = {0,1,0,-1};
int dy[] = {1,0,-1,0};
 
bool valid(int x, int y) {
    return 0 <= x && x < H && 0 <= y && y < W;
}

pair<int,int> qq[maxn*maxn], nxtt[maxn*maxn];

struct Queue
{
    pair<int,int> *q;
    int l = 0, r = 0;
    void push(pair<int,int> p) {
        q[r++] = p;  
    }
    void pop() {
        l++;
    }
    pair<int,int> front() {
        return q[l];
    }
    void clear() {
        l = 0;
        r = 0;
    }
    bool empty() {
        return l == r;
    }
};
 
int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> H >> W;
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            cin >> grid[i][j];
        }
    }
    if (H == 1 && W == 1) {
        cout << 1 << '\n';
        return 0;
    }
    Queue q, nxt;
    q.q = qq;
    nxt.q = nxtt;
    nxt.push({0,-1});
    char curr = grid[0][0];
    int ans = 0;
    int counter = 0;
    while (true) {
        int added = 0;
        //cout << "level " << ans << '\n';
        //cout << nxt.size() << '\n';
        while (!nxt.empty()) {
            q.push(nxt.front());
            nxt.pop();
        }
        nxt.clear();
        while (!q.empty()) {
            counter++;
            auto p = q.front(); q.pop();
            //cout << p.first << ' ' << p.second << '\n';
            for (int k = 0; k < 4; k++) {
                int nx = p.first + dx[k];
                int ny = p.second + dy[k];
                if (!valid(nx,ny)) continue;
                if (seen[nx][ny]) continue;
                if (grid[nx][ny] != curr) continue;
                seen[nx][ny] = true;
                q.push({nx,ny});
                nxt.push({nx,ny});
                added++;
            }
        }
        q.clear();
        curr = curr == 'R' ? 'F' : 'R';
        if (added == 0) break;
        ans++;
    }
    cout << ans << '\n';
}
