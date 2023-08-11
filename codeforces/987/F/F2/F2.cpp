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
bool seen[1 << MAXN][3];
bool isOrig[1 << MAXN];

int inverse(int x) {
    return ((1 << n) - 1) ^ x;
}

void dfs(int x, int type)
{
    if (seen[x][type] || (type == 1 && !isOrig[x])) return;
    seen[x][type] = true;
    if (type == 1) {
        dfs(x,2);
    }
    else {
        dfs(inverse(x),1);
        for (int i = 0; i < n; i++) {
            if (!(x & (1 << i))) {
                dfs(x|(1 << i),2);
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> A[i];
        isOrig[A[i]] = true;
    }
  
    int ans = 0;
    for (int i = 0; i < m; i++) {
        if (!seen[A[i]][1]) {
            dfs(A[i],1);
            ans++;
        }
    }
    cout << ans << '\n';

    return 0;
}
	

