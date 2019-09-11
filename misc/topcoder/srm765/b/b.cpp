#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int dist[55][55];
const int INF = 2e9;

struct T
{
    int x, y, d;
    bool isSide;

    bool operator<(const T& rhs) const {
        if (d != rhs.d) return d < rhs.d;
        if (x != rhs.x) return x < rhs.x;
        if (y != rhs.y) return y < rhs.y;
        if (isSide != rhs.isSide) return isSide < rhs.isSide;
    }
};

class Tunnel
{
public:
    int R, C;
    bool valid(int i, int j) {
        return 0 <= i && i < R && 0 <= j && j < C;
    }
    int minKeystrokes(vector<string> level, int rate) {
        R = level.size();
        C = level[0].size();
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                dist[i][j] = INF;
            }
        }
        for (int j = 0; j < C; j++) {
            if (level[0][j] == 'v') dist[0][j] = 0;
        }
        for (int i = 1; i < R; i++) {
            for (int j = 0; j < C; j++) {
                if (dist[i-1][j] < INF) {
                    for (int c2 = j-rate; c2 <= j+rate; c2++) {
                        if (c2 < 0 || c2 >= C) continue;
                        if (level[i][c2] == '#' || level[i-1][c2] == '#') continue;
                        dist[i][c2] = min(dist[i][c2],dist[i-1][j]+abs(j-c2));
                    }
                }
            }
        }

        /*
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                cout << dist[i][j] << ' ';
            }
            cout << '\n';
        }
        */
        int ans = INF;
        for (int j = 0; j < C; j++) {
            ans = min(ans,dist[R-1][j]);
        }
        if (ans == INF) return -1;
        return ans;
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    Tunnel t;
    vector<string> level = {"#...v.#"};
    int rate = 47;
    cout << t.minKeystrokes(level,rate) << '\n';
}

