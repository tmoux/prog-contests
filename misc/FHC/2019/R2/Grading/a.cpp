#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 305;
int dp[maxn][maxn*maxn]; //dp[curr][L][index of last deleted]
char grid[maxn][maxn];
int pt[maxn];
int s_level[maxn];
int maxLevel;

int f(int level, int L) {
    if (dp[level][L] != -1) return dp[level][L];
    if (level >= maxLevel-1) return dp[level][L] = 0;
    dp[level][L] = f(level+1,L) + 1;
    if (s_level[level+1] <= L) {
        dp[level][L] = min(dp[level][L],
                           f(level+2,L-s_level[level+1])
                           + (level==0?1:0));
    }
    //printf("dp[%d][%d]: %d\n",level,L,dp[level][L]);
    return dp[level][L];
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(0);
    int T; cin >> T;
    for (int qq = 1; qq <= T; qq++) {
        cout << "Case #" << qq << ": ";
        memset(pt,0,sizeof pt);
        memset(s_level,0,sizeof s_level);
        int H, S, K; cin >> H >> S >> K;
        for (int i = 1; i <= H; i++) {
            for (int j = 0; j < S; j++) {
                cin >> grid[j][i];
            }
        }
        for (int i = 0; i < S; i++) {
            pt[i] = 1;
        }
        int curr_level = 1;
        //evens are A's, odds are B's
        while (true) {
            //cout << curr_level << endl;
            for (int i = 0; i < S; i++) {
                char c = curr_level % 2 == 0 ? 'A' : 'B';
                while (pt[i] <= H && grid[i][pt[i]] == c) {
                    pt[i]++;
                    s_level[curr_level]++;
                }
            }
            /*
            cout << "curr level " << curr_level << ": " << s_level[curr_level] << '\n';
            for (int i = 0; i < S; i++) {
                cout << i << ": " << pt[i] << '\n';
            }
            */
            curr_level++;            
            bool canbreak = true;
            for (int i = 0; i < S; i++) {
                if (pt[i] <= H) {
                    canbreak = false;
                    break;
                }
            }
            if (canbreak) break;
        }
        maxLevel = curr_level;

        memset(dp,-1,sizeof dp);
        for (int i = 0; i < K; i++) {
            int L; cin >> L;
            cout << (f(0,L)) << ' ';
        }
        cout << '\n';
    }

}

