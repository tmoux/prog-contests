#include <bits/stdc++.h>
using namespace std;
using ll = long long;

string s;
const int INF = 2e9+9;

int dist[10][10];
int f(int x, int y) {

}

void dfs(int start, int curr, int d, int x, int y) {
    if (dist[start][curr] < d) {
        return;
    }
    dist[start][curr] = min(dist[start][curr],d);
    dfs(start,(curr+x)%10,d+1,x,y);
    dfs(start,(curr+y)%10,d+1,x,y);
}
int solve(int x, int y) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            dist[i][j] = INF;
        }
    }
    for (int i = 0; i < 10; i++) {
        dfs(i,(i+x)%10,0,x,y);
        dfs(i,(i+y)%10,0,x,y);
    }
    ll ans = 0;
    for (int i = 0; i < s.size() - 1; i++) {
        ans += dist[s[i]-'0'][s[i+1]-'0'];
        if (ans > INF) break;
    }
    return ans >= INF ? -1 : ans;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> s;
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++) {
            cout << solve(x,y) << ' ';
        }
        cout << '\n';
    }
    //cout << solve(0,1) << '\n';
}

