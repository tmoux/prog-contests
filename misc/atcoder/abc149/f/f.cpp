#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5, M = 1e9+7;
int n;
void madd(int& a, int b) {
    a += b;
    if (a >= M) a -= M;
}
int mult(int a, int b) {
    return (1LL*a*b) % M;
}
int msub(int a, int b) {
    madd(a,M-b);
    return a;
}
int modexp(int a, int b) {
    int res = 1;
    while (b > 0) {
        if (b&1) res = mult(res,a);
        a = mult(a,a);
        b >>= 1;
    }
    return res;
}
int inverse(int x) {
    return modexp(x,M-2);
}

vector<int> adj[maxn];
int sz[maxn];
void dfs(int i, int p) {
    sz[i] = 1;
    for (int j: adj[i]) {
        if (j == p) continue;
        dfs(j,i);
        sz[i] += sz[j];
    }
}

int e2[maxn], i2[maxn];

int f(int i, int p) {
    int res = 0;
    for (int j: adj[i]) {
        if (j == p) continue;
        madd(res,f(j,i));
    }
    int pr = 1;
    int s = n-1;
    pr = msub(pr,i2[s]);
    //cout << i << ": ";
    for (int j: adj[i]) {
        if (j == p) {
            int sj = n-sz[i];
            //cout << sj << ' ';
            pr = msub(pr,mult(i2[s-sj],
                         mult(msub(e2[sj],1),i2[sj])));
        }
        else {
            //cout << sz[j] << ' ';
            pr = msub(pr,mult(i2[s-sz[j]],
                         mult(msub(e2[sz[j]],1),i2[sz[j]])));
        }
    }
    //cout << '\n';
    pr = mult(pr,i2[1]);
    madd(res,pr);
    return res;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n-1; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    e2[0] = 1;
    for (int i = 1; i < maxn; i++) {
        e2[i] = mult(e2[i-1],2);
    }
    i2[0] = 1;
    i2[1] = inverse(2);
    for (int i = 2; i < maxn; i++) {
        i2[i] = mult(i2[i-1],i2[1]);
    }
    dfs(1,1);
    f(1,1);
    cout << f(1,1) << '\n';
}

