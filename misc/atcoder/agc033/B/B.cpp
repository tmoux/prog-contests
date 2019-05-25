#include <bits/stdc++.h>
using namespace std;
using ll = long long;

map<char,int> dx = {{'L',0},{'R',0},{'U',-1},{'D',1}};
map<char,int> dy = {{'L',-1},{'R',1},{'U',0},{'D',0}};
const int maxn = 2e5+5;
int H, W, N;
string s, t;

bool valid(int x, int y) {
    return 1 <= x && x <= H && 1 <= y && y <= W;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> H >> W >> N;
    int x, y; cin >> x >> y;
    cin >> s >> t;
    bool poss = false;
    int cx = x, cy = y;
    //try left-up
    for (int i = 0; i < N; i++) {
        if (s[i] == 'L') cy--;
        else if (s[i] == 'U') cx--;
        if (poss || !valid(cx,cy)) {
            poss = true;
            break;
        }
        if (t[i] == 'R' && valid(cx,cy+1)) cy++;
        else if (t[i] == 'D' && valid(cx+1,cy)) cx++;
    }
    cx = x, cy = y;
    //try left-down
    for (int i = 0; i < N; i++) {
        if (s[i] == 'L') cy--;
        else if (s[i] == 'D') cx++;
        if (poss || !valid(cx,cy)) {
            poss = true;
            break;
        }
        if (t[i] == 'R' && valid(cx,cy+1)) cy++;
        else if (t[i] == 'U' && valid(cx-1,cy)) cx--;
    }
    cx = x, cy = y;
    //try right-up
    for (int i = 0; i < N; i++) {
        if (s[i] == 'R') cy++;
        else if (s[i] == 'U') cx--;
        if (poss || !valid(cx,cy)) {
            poss = true;
            break;
        }
        if (t[i] == 'L' && valid(cx,cy-1)) cy--;
        else if (t[i] == 'D' && valid(cx+1,cy)) cx++;
    }
    cx = x, cy = y;
    //try right-down
    for (int i = 0; i < N; i++) {
        if (s[i] == 'R') cy++;
        else if (s[i] == 'D') cx++;
        if (poss || !valid(cx,cy)) {
            poss = true;
            break;
        }
        if (t[i] == 'L' && valid(cx,cy-1)) cy--;
        else if (t[i] == 'U' && valid(cx-1,cy)) cx--;
    }

    cout << (poss ? "NO" : "YES") << '\n';
}

