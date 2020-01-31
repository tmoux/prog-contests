#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int M = 1e9+7;
void madd(int& a, int b) {
    a += b;
    if (a >= M) a -= M;
}
int mult(int a, int b) {
    return (1LL*a*b) % M;
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

const int maxn = 1005;
int n, m;
char grid[maxn][maxn];

int parent[maxn*maxn]; //memset to -1
set<int> comps;

int Find(int x) {
    return parent[x] < 0 ? x : parent[x] = Find(parent[x]);
}

void Union(int x, int y) {
    x = Find(x);
    y = Find(y);
    if (x == y) return;
    if (parent[x] > parent[y]) swap(x,y);
    parent[x] += parent[y];
    parent[y] = x;
}

int cv(int i, int j) {
    return i*m+j;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    //freopen("cave.in","r",stdin); freopen("cave.out","w",stdout);
    memset(parent,-1,sizeof parent);
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }
    int ans = 1;
    for (int i = n-2; i >= 1; i--) {
        /*
        vector<int> pre(m);
        for (int j = 1; j < m; j++) {
            if (grid[i+1][j] == '#') continue;
            pre[j] = Find(cv(i+1,j));
        }
        */
        for (int j = 1; j < m; j++) {
            if (grid[i][j] == '#') continue;
            if (grid[i][j+1] == '.') Union(cv(i,j+1),cv(i,j));
            if (grid[i][j-1] == '.') Union(cv(i,j-1),cv(i,j));
            if (grid[i+1][j] == '.') Union(cv(i+1,j),cv(i,j));
        }
        comps.clear();

        //cout << "i = " << i << endl;
        for (int k = i; k <= n-2; k++) {
            for (int j = 0; j < m; j++) {
                if (grid[k][j] == '#') {
                    //cout << '#' << ' ';
                }
                else {
                    comps.insert(Find(cv(k,j)));
                    //cout << Find(cv(k,j)) << ' ';
                }
            }
            //cout << '\n';
        }
        /*
        for (int j = 1; j < m; j++) {
            if (grid[i][j] == '#') continue;
            comps.insert(Find(cv(i,j)));
        }
        for (int j = 1; j < m; j++) {
            if (grid[i+1][j] == '#') continue;
            if (Find(cv(i+1,j)) != pre[j]) {
                if (comps.count(pre[j])) comps.erase(pre[j]);
            }
        }
        */
        //cout << i << ": " << comps.size() << endl;
        int add = modexp(2,comps.size());
        madd(add,M-1);
        madd(ans,add);
    }
    cout << ans << '\n';
}

