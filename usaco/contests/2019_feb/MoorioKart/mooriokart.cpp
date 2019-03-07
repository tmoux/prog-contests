#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1505, M = 1e9+7;
int madd(int a, int b) {
    return (a+b) % M;
}
int mult(int a, int b) {
    return (1LL*a*b) % M;
}
int modexp(int a, ll b) {
    int r = 1;
    while (b) {
        if (b&1) r = mult(r,a);
        a = mult(a,a);
        b >>= 1;
    }
    return r;
}
int inverse(int x) {
    return modexp(x,M-2);
}
int ch2(int x) {
    return mult(mult(x,x-1),inverse(2));
}
int N, m, X, Y, K;
struct Edge
{
    int to, w;
};
vector<Edge> adj[maxn];

struct Tree
{
    int n;
    map<int,int> cnt; //maps distance to count            
};

bool seen[maxn];

void ffill(int i, vector<int>& comp) {
    comp.push_back(i);
    seen[i] = true;
    for (Edge e: adj[i]) {
        if (seen[e.to]) continue;
        ffill(e.to,comp);
    }
}

void dfs_len(int i, int p, int d, map<int,int>& cnt) {
    if (d > 0) cnt[d]++;
    for (Edge e: adj[i]) {
        if (e.to == p) continue;
        dfs_len(e.to,i,d+e.w,cnt);
    }
}

Tree getTree(const vector<int>& comp) {
    Tree r;
    r.n = comp.size();
    for (int i: comp) {
        dfs_len(i,i,0,r.cnt);
    }
    for (auto& p: r.cnt) {
        p.second /= 2;
    }
    return r;
}

Tree trees[maxn];
int pt = 1;
int dp[5000][5000]; //# of paths using the first i nodes, that sum up to y (K-x included)

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    freopen("mooriokart.in","r",stdin); freopen("mooriokart.out","w",stdout);
    cin >> N >> m >> X >> Y;
    K = N - m; //K = # of components
    for (int i = 0; i < m; i++) {
        int a, b, d; cin >> a >> b >> d;
        adj[a].push_back({b,d});
        adj[b].push_back({a,d});
    }
    for (int i = 1; i <= N; i++) {
        if (!seen[i]) {
            vector<int> comp;
            ffill(i,comp);
            trees[pt++] = getTree(comp);
            /*
            cout << trees[pt-1].n << '\n';
            for (auto p: trees[pt-1].cnt) {
                cout << p.first << ": " << p.second << '\n';
            }
            cout << '\n';
            */
        }
    }

    //calculate total sum
    assert(pt == K+1);
    int tot = 1; //tot = product of ch2 paths from each tree
    for (int i = 1; i <= K; i++) 
        tot = mult(tot,ch2(trees[i].n));        
    int sumall = 0; //sum of all path lengths, need to mult by 2^(K-1)*(K-1)!
    for (int i = 1; i <= K; i++) {
        for (auto p: trees[i].cnt) {
            sumall = madd(sumall,mult(p.second,mult(p.first,mult(tot,inverse(ch2(trees[i].n))))));                
        }
    }
    int sumFromX = mult(tot,mult(K,X));
    sumall = madd(sumall,sumFromX); //need to multiply by 2^(K-1) * ((K-1)!)


    //now do dp to count sum of paths strictly less than Y
    Y = Y - K * X; //can be negative
    dp[0][0] = 1;
    for (int i = 1; i <= K; i++) {
        for (auto p: trees[i].cnt) {
            for (int y = 0; y + p.first < Y; y++) {
                dp[i][y+p.first] = madd(dp[i][y+p.first],mult(dp[i-1][y],p.second));
            }
        }
    }
    int takeout = 0;
    for (int y = 0; y < Y; y++) {
        takeout = madd(takeout,mult(dp[K][y],madd(y,mult(K,X))));
        //cout << y << ": " << dp[K][y] << '\n';
    }
    sumall = (sumall - takeout + M) % M;
    //multiply by 2^(K-1) * (K-1)!
    sumall = mult(sumall,modexp(2,K-1));
    for (int i = 2; i <= K-1; i++) sumall = mult(sumall,i);            
    cout << sumall << '\n';
    return 0;
}

