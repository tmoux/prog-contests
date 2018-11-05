#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 2005, INF = 1e9+9;
char grid[maxn][maxn];
int n, k, dp[maxn][maxn];

void amin(int& i, int j) {
    i = min(i,j);
}
void amax(int& i, int j) {
    i = max(i,j);
}

bool vis[maxn][maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        for (int j = 0; j < n; j++) {
            grid[i][j] = s[j];
            dp[i][j] = INF;
        }
    }
    int pref = 0;
    dp[0][0] = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i > 0) amin(dp[i][j],dp[i-1][j]);
            if (j > 0) amin(dp[i][j],dp[i][j-1]);
            if (grid[i][j] != 'a') ++dp[i][j];
            if (dp[i][j] <= k) {
                amax(pref,i+j+1);
            }
        }
    }

    vector<char> ans(pref,'a');
    vector<pair<int,int>> poss;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i+j+1 == pref && dp[i][j] <= k) {
                poss.push_back({i,j});        
                //cout << i << ' ' << j << '\n';
            }
        }
    }
    if (poss.empty()) {
        poss.push_back({0,0});
        ans.push_back(grid[0][0]);
        pref = 1;
    }
    auto valid = [](int i, int j) {
        return 0 <= i && i < n && 0 <= j && j < n;
    };

    for (int i = 1; i <= 2*n-1-pref; i++) {
        vector<pair<int,int>> news;
        char minchar = 'z';
        for (auto& p: poss) {
            for (int dx : {0,1}) {
                int dy = 1-dx;
                if (!valid(p.first+dx,p.second+dy)) continue;
                if (vis[p.first+dx][p.second+dy]) continue;
                vis[p.first+dx][p.second+dy] = true;
                char c = grid[p.first+dx][p.second+dy];
                if (c < minchar) {
                    minchar = c;
                    news = {{p.first+dx,p.second+dy}};
                }
                else if (c == minchar) {
                    news.push_back({p.first+dx,p.second+dy});
                }
            }
        }
        //cout << i << ": " << minchar << '\n';
        //cout << ans.size() << '\n';
        ans.push_back(minchar);
        poss = news;
    }

    //output
    for (char c: ans) {
        cout << c;
    }
    cout << '\n';
    
    return 0;
}

