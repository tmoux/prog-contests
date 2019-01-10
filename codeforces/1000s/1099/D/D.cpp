#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
const int maxk = 17;
int n;
int depth[maxn];
vector<int> child[maxn];
int par[maxk][maxn];
int sum[maxn], val[maxn];
bool POSS = true;

void DFS(int i) {
    if (i == 1) val[i] = sum[i];
    else {
        if (sum[i] == -1) {

        }
        else {
            int j = i;
            if (par[0][j] != -1 && val[par[0][j]] == -1) {
                j = par[0][j];
                if (sum[i] < sum[par[0][j]]) {
                    POSS = false;
                    return;
                }
                val[j] = sum[i] - sum[par[0][j]];
                sum[j] = sum[i];
                val[i] = 0;
            }
            else {
                if (sum[i] < sum[par[0][i]]) {
                    POSS = false;
                    return;
                }
                val[i] = sum[i] - sum[par[0][i]];
            }
        }
    }
    //
    vector<int> nxt;
    for (int j: child[i]) {
        nxt.push_back(j);
    }
    sort(nxt.begin(),nxt.end(),[](int a, int b) {
            return sum[a] < sum[b];
            });
    for (int j: nxt) DFS(j);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    depth[1] = 1;
    memset(par,-1,sizeof(par));
    for (int i = 2; i <= n; i++) {
        int p; cin >> p;
        child[p].push_back(i);
        depth[i] = depth[p]+1;
        par[0][i] = p;
    }
    for (int i = 1; i <= n; i++) cin >> sum[i];
    //sparse table
    for (int k = 1; k < maxk; k++) {
        for (int i = 1; i <= n; i++) {
            if (par[k-1][i] == -1) par[k][i] = -1;
            else par[k][i] = par[k-1][par[k-1][i]];
        }
    }
    memset(val,-1,sizeof(val));
    DFS(1);
    if (!POSS) {
        cout << -1 << '\n';
        return 0;
    }
    else {
        ll total = 0;
        for (int i = 1; i <= n; i++) {
            total += max(0,val[i]);
            //cout << i << ": " << val[i] << '\n';
        }
        cout << total << '\n';
    }
    

    return 0;
}

