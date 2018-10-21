#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <set>
using namespace std;
typedef long long ll;

const int maxn = 200005;
set<int> adj[maxn];
int n, m, k, p;
bool seen[maxn];
vector<int> tour;

int getmax(int n, int k) {
    return ((2*n) % k ? 2*n/k+1 : 2*n/k);
}

void dfs(int i, int par) {
    seen[i] = true;
    tour.push_back(i);
    for (int j: adj[i]) {
        if (!seen[j]) dfs(j,i);
    }
    tour.push_back(par);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    //input
    cin >> n >> m >> k;
    p = getmax(n,k);
    for (int i = 0; i < m; i++) {
        int xi, yi; cin >> xi >> yi;
        if (xi != yi) {
            adj[xi].insert(yi);
            adj[yi].insert(xi);
        }
    }
    dfs(1,-1);
    //output
    for (int i = 0; i < k; i++) {
        int istart = i*p, iend = min(2*n-1,(i+1)*p);
        if (istart >= iend) istart = iend - 1;
        cout << (iend - istart) << ' ';
        for (int j = istart; j < iend; j++) {
            cout << tour[j] << ' ';
        }
        cout << '\n';
    }
   


    return 0;
}
	

