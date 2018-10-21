#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

const int maxn = 200005;
vector<int> adj[maxn];
int color[maxn];
int n, maxk = 0;

void dfs(int i, int c, int par) {
    color[i] = c;
    maxk = max(maxk,c);
    int nxtcolor = 1;
    for (int j: adj[i]) {
        if (j != par) {
            while (nxtcolor == color[i] || nxtcolor == color[par]) {
                nxtcolor++;
            }
            dfs(j,nxtcolor++,i);
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n-1; i++) {
        int xi, yi; cin >> xi >> yi;
        adj[xi].push_back(yi);
        adj[yi].push_back(xi);
    }
    dfs(1,1,0);
    //output
    cout << maxk << '\n';
    for (int i = 1; i <= n; i++) {
        cout << color[i] << ' ';
    }


    return 0;
}
	

