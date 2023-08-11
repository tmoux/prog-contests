#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 5;
int n;
vector<int> edges[maxn][maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    #ifdef OFFLINE
    freopen("in","r",stdin);
    #endif
    cin >> n;
    for (int i = 0; i < n; i++) {
    	int c1, v, c2; cin >> c1 >> v >> c2;
    	c1--; c2--;
		edges[c1][c2].push_back(v);
		edges[c2][c1].push_back(v);	
    }
    for (int i = 0; i <= 3; i++) {
    	for (int j = 0; j <= 3; j++) {
    		sort(edges[i][j].begin(),edges[i][j].end());
    	}
    }

    for (int i = 0; i < (1 << 16); i++) {
    	
    }


    return 0;
}