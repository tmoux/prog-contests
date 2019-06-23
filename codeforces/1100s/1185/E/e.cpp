#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2005;
int n, m;
char grid[maxn][maxn];
bool seen[35];
int X1[35], X2[35], Y1[35], Y2[35];

vector<int> ans[35];

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while (t--) {
        cin >> n >> m;
        memset(seen,false,sizeof seen);
        for (int i = 0; i < 35; i++) {
            X1[i] = Y1[i] = maxn;
            X2[i] = Y2[i] = 0;
        }

        int maxseen = -1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> grid[i][j];
                int g = grid[i][j]-'a';
                if ('a' <= grid[i][j] && grid[i][j] <= 'z') {
                    seen[g] = true;
                    maxseen = max(maxseen,g);
                }
                X1[g] = min(X1[g],i);
                Y1[g] = min(Y1[g],j);
                X2[g] = max(X2[g],i);
                Y2[g] = max(Y2[g],j);
            }
        }
        vector<int> pos;
        bool poss = true;
        for (int i = maxseen; i >= 0; i--) {
            if (i == maxseen) {
                pos = {X1[i],Y1[i],X1[i],Y1[i]};
            }
            if (!seen[i]) {
                ans[i] = pos;
            }
            else {
                if (X1[i] != X2[i] && Y1[i] != Y2[i]) {
                    poss = false;
                    break;
                }

                for (int a = X1[i]; a <= X2[i]; a++) {
                    for (int b = Y1[i]; b <= Y2[i]; b++) {
                        if (grid[a][b] == '.') {
                            poss = false;
                            break;
                        }
                        if (grid[a][b] < (char)('a'+i)) {
                            poss = false;
                            break;
                        }
                    }
                }
                ans[i] = {X1[i],Y1[i],X2[i],Y2[i]};
            }
        }
        if (!poss) {
            cout << "NO\n";
        }
        else {
            cout << "YES\n";
            cout << (maxseen+1) << '\n';
            for (int i = 0; i <= maxseen; i++) {
                assert(ans[i].size() == 4);
                printf("%d %d %d %d\n",ans[i][0]+1,ans[i][1]+1,ans[i][2]+1,ans[i][3]+1);
            }
        }
    }

}

