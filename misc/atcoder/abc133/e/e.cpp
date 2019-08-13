#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int N, K;
vector<int> adj[100005];
const int M = 1e9+7;
int mult(int a, int b) {
    return (1LL*a*b) % M;
}
int fac[100005];
int modexp(int a, int b) {
    int res = 1;
    while (b) {
        if (b&1) res = mult(res,a);
        a = mult(a,a);
        b >>= 1;
    }
    return res;
}
int inverse(int x) {
    return modexp(x,M-2);
}

int dfs(int i, int p) {
    int num = i == 1 ? K-1 : K-2;
    int numChilds = i == 1 ? adj[i].size() : adj[i].size() - 1;
    if (num - numChilds < 0) {
        return 0;
    }
    int res = mult(fac[num],inverse(fac[num-numChilds]));
    /*
    cout << num << '\n';
    cout << i << ": " << res << '\n';
    */
    for (int j: adj[i]) {
        if (j == p) continue;
        res = mult(res,dfs(j,i));
    }
    //cout << i << ": " << res << '\n';
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> K;
    for (int i = 0; i < N - 1; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    fac[0] = 1;
    for (int i = 1; i <= K; i++) {
        fac[i] = mult(fac[i-1],i);
    }
    int ans = mult(K,dfs(1,1));
    cout << ans << '\n';
}

