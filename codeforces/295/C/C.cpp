#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxk = 5005, maxn = 55, M = 1e9+7;
int n, k;
int c1 = 0, c2 = 0;
ll modexp(ll x, ll n) {
    if (n == 0) return 1;
    if (n == 1) return x%M;
    if (n%2==0) return modexp((x*x)%M,n/2);
    return (x*modexp((x*x)%M,n/2))%M;
}
ll modInverse(ll x) {
    return modexp(x,M-2);
}
void madd(int& a, int b) {
    a = (a+b) % M;
}
int mult(int a, int b) {
    return (1LL*a*b) % M;
}
int fac[maxn];
int comb(int N, int K) {
    return mult(fac[N],mult(modInverse(fac[K]),modInverse(fac[N-K])));
}

int dist[maxn][maxn][2];
int ans[maxn][maxn][2];

struct State
{
    int a1, a2;
    bool isR;
    State() {}
    State(int _a1, int _a2, bool _isR) {
        a1 = _a1;
        a2 = _a2;
        isR = _isR;
    }
    bool operator==(const State& r) {
        return a1 == r.a1 && a2 == r.a2 && isR == r.isR;
    }
};

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> k;
    fac[0] = 1;
    for (int i = 1; i <= n; i++) {
        fac[i] = mult(i,fac[i-1]);
    }
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        int ai; cin >> ai;
        ai /= 50;
        if (ai == 1) c1++;
        else c2++;
    }
    k /= 50;
    queue<State> q;
    memset(dist,-1,sizeof dist);
    q.push({0,0,0});
    dist[0][0][0] = 0;
    ans[0][0][0] = 1;
    while (!q.empty()) {
        auto f = q.front(); q.pop();
        //printf("[%d][%d], %s, dist = %d, # ways = %d\n",f.a1,f.a2,(f.isR?"right":"left"),dist[f.a1][f.a2][f.isR],ans[f.a1][f.a2][f.isR]);
        int d = dist[f.a1][f.a2][f.isR];
        int a = f.a1; int b = f.a2; int c = f.isR;
        int l, s;
        if (c) l = f.a1, s = f.a2;
        else l = c1 - f.a1, s = c2 - f.a2;
        for (int i = 0; i <= l; i++) {
            for (int j = 0; j <= s; j++) {
                if (!i && !j) continue;
                if (i+2*j > k) continue;
                int x, y, z;
                if (!c) x = f.a1 + i, y = f.a2 + j;
                else x = f.a1 - i, y = f.a2 - j;
                z = 1 - c;
                int wy = 1;
                wy = mult(wy,ans[a][b][c]);
                wy = mult(wy,comb(l,i));
                wy = mult(wy,comb(s,j));
                if (dist[x][y][z] == -1) {
                    q.push({x,y,z});
                    dist[x][y][z] = dist[a][b][c] + 1;
                    ans[x][y][z] = wy;
                }
                else if (dist[x][y][z] == dist[a][b][c] + 1) {
                    madd(ans[x][y][z],wy);
                }
            }
        }
    }
    if (dist[c1][c2][1] == -1) {
        cout << "-1\n0\n";
    }
    else {
        cout << dist[c1][c2][1] << '\n';
        cout << ans[c1][c2][1] << '\n';
    }
}
