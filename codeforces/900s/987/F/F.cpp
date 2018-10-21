#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <stdlib.h>
#include <cstring>
#include <bitset>
using namespace std;
typedef long long ll;

const int MAXN = 22;
int n, m, A[1 << MAXN];
int parent[1 << MAXN];
bool seen[1 << MAXN];
bool isComp[1 << MAXN];

void dfs(int i, int par) {
    if (!seen[i]) return;
    seen[i] = false;
    parent[i] = par;
    int inverse = ((1 << n) - 1) ^ i;
    //cout << i << ' ' << inverse << '\n';
    vector<int> bits;
    for (int a = 0; a < n; a++) {
        if (inverse & (1 << a)) bits.push_back(a);
    }
    for (int j = 0; j < (1 << bits.size()); j++) {
        int nxt = inverse;
        for (int k = 0; k < bits.size(); k++) {
            if (j & (1 << k)) nxt &= ~(1 << bits[k]);
        }
        if (!seen[i]) dfs(nxt,par);
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < (1 << n); i++) {
        parent[i] = i;
    }
   
    for (int i = 0; i < m; i++) {
        cin >> A[i];
        seen[A[i]] = true;
    }
  
    for (int i = 0; i < m; i++) {
        if (parent[A[i]] == A[i]) {
            dfs(A[i],A[i]);
        }
    }
    //compute number of components
    //for (int i = 0; i < m; i++) {
    //    cout << A[i] << ' ' << parent[A[i]] << '\n';
    //}
    int ans = 0;
    for (int i = 0; i < m; i++) {
        isComp[parent[A[i]]] = true;
    }
    for (int i = 0; i < (1 << n); i++) {
        if (isComp[i]) ans++;
    }

    cout << ans << '\n';


    return 0;
}
	

