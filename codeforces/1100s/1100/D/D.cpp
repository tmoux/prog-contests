#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

pair<int,pair<int,int>> ask(int x, int y) {
    cout << x << ' ' << y << endl;
    int k, xx, yy; cin >> k >> xx >> yy;
    assert(k != 0);
    if (k == -1) exit(0);
    return make_pair(k,make_pair(x,y));
}

const int maxn = 1005;
int xpos[maxn], ypos[maxn];
bool blocked[maxn][maxn];

pair<int,pair<int,int>> tryMove(int& x, int& y, int a, int b) {
    //[x,y] -> [a,b]
    //try to move diagonally
    int nx;
    if (x < a) nx = x + 1;
    else if (x > a) nx = x - 1;
    else nx = x;
    int ny;
    if (y < b) ny = y + 1;
    else if (y > b) ny = y - 1;
    else ny = y;
    //assert(x != nx || y != ny);
    assert(1 <= nx && nx <= 999 && 1 <= ny && ny <= 999);
    if (blocked[nx][ny]) {
        //move to the side, should end;
        ask(x,ny); 
        assert(false);
    }
    else {
        //just move there
        x = nx;
        y = ny;
        return ask(nx,ny);
    }
}

int main()
{
    int kx, ky; cin >> kx >> ky;
    for (int k = 1; k <= 666; k++) {
        cin >> xpos[k] >> ypos[k];    
        blocked[xpos[k]][ypos[k]] = true;
    }
    int mx = 500, my = 500;
    while (kx != mx && ky != my) {
        auto p = tryMove(kx,ky,mx,my);
        int xx = p.second.first;
        int yy = p.second.second;
        int k = p.first;
        blocked[xpos[k]][ypos[k]] = false;
        blocked[xx][yy] = true;
        xpos[k] = xx;
        ypos[k] = yy;
    }

    assert(kx == mx && ky == my);
    //divide into four quadrants
    pair<int,int> q1 = {1,1},
                  q2 = {999,1},
                  q3 = {999,999},
                  q4 = {1,999};
    int c1 = 0, c2 = 0, c3 = 0, c4 = 0;
    for (int k = 1; k <= 666; k++) {
        if (xpos[k] < 500 && ypos[k] < 500) c1++;
        else if (xpos[k] > 500 && ypos[k] < 500) c2++;
        else if (xpos[k] > 500 && ypos[k] > 500) c3++;
        else c4++;
    }
    int tx, ty;
    int which = min(min(c1,c2),min(c3,c4));
    if (c1 == which) {
        tx = q1.first; ty = q1.second;
    }
    else if (c2 == which) {
        tx = q2.first; ty = q2.second;
    }
    else if (c3 == which) {
        tx = q3.first; ty = q3.second;
    }
    else {
        tx = q4.first; ty = q4.second;
    }
    while (kx != tx && ty != ty) {
        auto p = tryMove(kx,ky,tx,ty);
        int xx = p.second.first;
        int yy = p.second.second;
        int k = p.first;
        blocked[xpos[k]][ypos[k]] = false;
        blocked[xx][yy] = true;
        xpos[k] = xx;
        ypos[k] = yy;
    }

    return 0;
}
