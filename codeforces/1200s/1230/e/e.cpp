#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5, M = 1e9+7;
const int maxk = 18;
int n;
vector<int> adj[maxn];
ll x[maxn];
int par[maxk][maxn];
ll gc[maxk][maxn];
int depth[maxn];

void root(int i, int p) {
    depth[i] = depth[p] + 1;
    par[0][i] = p;
    gc[0][i] = __gcd(x[i],x[p]);
    for (int k = 1; k < maxk; k++) {
        par[k][i] = par[k-1][par[k-1][i]];
        int jmp = par[k-1][i];
        gc[k][i] = __gcd(gc[k-1][i],gc[k-1][jmp]);
    }
    for (int j: adj[i]) {
        if (j == p) continue;
        root(j,i);
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> x[i];
    }
    for (int i = 0; i < n-1; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    root(1,0);
    /*
    for (int i = 1; i <= n; i++) {
        for (int k = 0; k < 4; k++) {
            cout << i << ' ' << k << ": " << gc[k][i] << '\n';
        }
    }
    */
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        ll curr = x[i];
        int j = i;
        ll cum = 0;
        //cout << "start " << i << ":\n";
        while (j != 0) {
            int pj = j;
            if (gc[0][j] == 0 || curr % gc[0][j] != 0 || par[0][j] == 0) {
                j = par[0][j];
                ll add = curr;
                cum = (cum + add) % M;
                curr = __gcd(x[j],curr);
                //printf("j = %d, add = %d, curr = %d\n",j,add,curr);
            }
            else {
                for (int k = maxk-1; k >= 0; k--) {
                    int nj = par[k][j];
                    if (nj == 0) continue;
                    if (gc[k][j] == 0 || curr % gc[k][j] == 0) {
                        j = nj;    
                    }
                }
                j = par[0][j];
                ll add = ((curr%M) * 1LL*(depth[pj]-depth[j])) % M;
                cum = (cum + add) % M;
                curr = __gcd(x[j],curr);
                //printf("j = %d, add = %d, curr = %d\n",j,add,curr);
            }
        }
        //cout << i << ": " << cum << '\n';
        ans = (ans + cum) % M;
    }
    cout << ans << '\n';
}

