#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define x first
#define y second
map<char,pair<int,int>> mp = {{'U',{0,1}},{'D',{0,-1}},{'L',{-1,0}},{'R',{1,0}}};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int a, b; cin >> a >> b;
    string s; cin >> s;
    int n = s.size();
    vector<pair<int,int>> delta(n+1);
    for (int i = 0; i <= n; i++) {
        if (i == 0) delta[i] = {0,0};
        else {
            int dx = mp[s[i-1]].x;
            int dy = mp[s[i-1]].y;
            delta[i] = {delta[i-1].x+dx,delta[i-1].y+dy};
        }
    }
    for (int i = 0; i < n; i++) {
        int dx = delta[n].x;
        int dy = delta[n].y;
        int cx = delta[i].x;
        int cy = delta[i].y;
        bool poss = true;
        int multX, multY;
        if (dx == 0) {
            if (a == cx) multX = -1;
            else poss = false;
        }
        else {
            if ((a-cx) % dx == 0 && (a-cx)/dx >= 0) {
                multX = (a-cx)/dx;
            }
            else poss = false;
        }
        if (dy == 0) {
            if (b == cy) multY = -1;
            else poss = false;
        }
        else {
            if ((b-cy) % dy == 0 && (b-cy)/dy >= 0) {
                multY = (b-cy)/dy;
            }
            else poss = false;
        }

        if (!(multX == -1 || multY == -1 || multX == multY)) poss = false;

        if (!poss) continue;
        else {
            //cout << cx << ' ' << cy << '\n';
            cout << "Yes\n";
            return 0;
        }
    }
    cout << "No\n";
    return 0;
}

