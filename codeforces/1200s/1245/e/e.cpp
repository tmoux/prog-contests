#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 15;
int h[maxn][maxn];

double dp[maxn][maxn];
pair<int,int> nxt(pair<int,int> curr, int r) {
    //cout << curr.first << ' ' << curr.second << ' ' << r << endl;
    if (r == 0) return curr;
    if (((curr.first%2==1) && curr.second == 9) || 
        ((curr.first%2==0) && curr.second == 0)) {
        return nxt({curr.first-1,curr.second},r-1);
    }
    if (curr.first&1) {
        int diff = min(r,9-curr.second);
        return nxt({curr.first,curr.second+diff},r-diff);
    }
    else {
        int diff = min(r,curr.second);
        return nxt({curr.first,curr.second-diff},r-diff);
    }
}

bool valid(pair<int,int> p) {
    return 0 <= p.first && p.first < 10 && 0 <= p.second && p.second < 10;
}

int main() {
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cout << fixed << setprecision(10);
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            cin >> h[i][j];
        }
    }
    dp[0][0] = 0;
    for (int i = 1; i <= 6; i++) {
        dp[0][i] = 6;
    }
    for (int i = 0; i < 10; i++) {
        if (i&1) {
            for (int j = 9; j >= 0; j--) {
                dp[i][j] = 1;
                int f = 0;
                for (int r = 1; r <= 6; r++) {
                    pair<int,int> nx = nxt({i,j},r);
                    if (!valid(nx)) {
                        f++;
                        continue;
                    }
                    assert(valid(nx));
                    dp[i][j] += 1.0/6*min(dp[nx.first][nx.second],dp[nx.first-h[nx.first][nx.second]][nx.second]);
                }
                dp[i][j] *= 6/(6-f);
                //cout << i << ' ' << j << ": " << dp[i][j] << '\n';
            }
        }
        else {
            for (int j = 0; j <= 9; j++) {
                if (i == 0 && j <= 6) continue;
                //cout << i << ' ' << j << endl;
                dp[i][j] = 1;
                int f = 0;
                for (int r = 1; r <= 6; r++) {
                    pair<int,int> nx = nxt({i,j},r);
                    if (!valid(nx)) {
                        f++;
                        continue;
                    }
                    //printf("(%d, %d): r = %d: (%d, %d)\n",i,j,r,nx.first,nx.second);
                    //printf("[%d][%d] = %.10f\n",nx.first,nx.second,dp[nx.first][nx.second]);
                    dp[i][j] += 1.0/6*min(dp[nx.first][nx.second],dp[nx.first-h[nx.first][nx.second]][nx.second]);
                }
                //printf("dp[%d][%d]: %.10f, f = %d\n",i,j,dp[i][j],f);
                dp[i][j] *= 6/(6-f);
                //cout << i << ' ' << j << ": " << dp[i][j] << '\n';
            }
        }
    }
    cout << fixed << setprecision(10) << dp[9][0] << '\n';
}

