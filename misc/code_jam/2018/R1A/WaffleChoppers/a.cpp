#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 105;
char grid[maxn][maxn];

int main()
{
    int t; cin >> t;
    for (int qq = 1; qq <= t; qq++) {
        cout << "Case #" << qq << ": ";
        int R, C, H, V; cin >> R >> C >> H >> V;
        int cnt = 0;
        for (int i = 0; i < R; i++) 
            for (int j = 0; j < C; j++) {
                cin >> grid[i][j];
                if (grid[i][j] == '@') cnt++;
            }
        if (cnt == 0) {
            cout << "POSSIBLE\n";
            continue;
        }
        int partitions = (H+1)*(V+1);
        if (cnt % partitions != 0) {
            cout << "IMPOSSIBLE\n";
        }
        else {
            vector<int> verts;
            int desire = cnt / (V+1);
            //cout << "desire = " << desire << '\n';
            int curr = 0;
            for (int i = 0; i < C; i++) {
                for (int j = 0; j < R; j++) {
                    if (grid[j][i] == '@') curr++;
                }
                if (curr >= desire) {
                    verts.push_back(i);
                    curr = 0;
                }
                //cout << i << ": " << curr << '\n';
            }
            /*
            cout << "Case " << qq << '\n';
            for (int i: verts) {
                cout << i << '\n';
            }
            */
            vector<int> horiz;
            desire = cnt / (H+1);
            //cout << "desire = " << desire << '\n';
            curr = 0;
            for (int i = 0; i < R; i++) {
                for (int j = 0; j < C; j++) {
                    if (grid[i][j] == '@') curr++;
                }
                if (curr >= desire) {
                    horiz.push_back(i);
                    curr = 0;
                }
                //cout << i << ": " << curr << '\n';
            }
            /*
            cout << "Case " << qq << '\n';
            for (int i: horiz) {
                cout << i << '\n';
            }
            */
            if (verts.size() != V + 1 || horiz.size() != H + 1) {
                cout << "IMPOSSIBLE\n";
                continue;
            }
            else {
                int need = cnt / ((H+1)*(V+1));
                bool poss = true;
                for (int i = 0; i < horiz.size(); i++) {
                    for (int j = 0; j < verts.size(); j++) {
                        int count = 0;
                        //cout << horiz[i] << ' ' << verts[j] << ":\n";
                        for (int r = i==0?0:horiz[i-1]+1; r <= horiz[i]; r++) {
                            for (int c = j==0?0:verts[j-1]+1; c <= verts[j]; c++) {
                                //printf("(%d, %d)\n",r,c);
                                if (grid[r][c] == '@') count++;
                            }
                        }
                        //cout << horiz[i] << ' ' << verts[j] << ": " << count << '\n';
                        if (count != need) poss = false;
                    }
                }
                cout << (poss?"POSSIBLE":"IMPOSSIBLE") << '\n';
            }
        }
    }

}

