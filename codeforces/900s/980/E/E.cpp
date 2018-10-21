#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <queue>
#include <cstring>
using namespace std;
typedef long long ll;

const int maxn = 1000005;
const int maxk = 21;
int n, k;
vector<int> adj[maxn];
bool included[maxn];

struct DiTree
{
    int numIncluded = 0;
    vector<int> childs[maxn];
    int dist[maxn]; //distance from root
    int anc[maxn][maxk];
    bool isInclude[maxn];
    
    void dfs(int j, int d, int par) {
        dist[j] = d;
        for (int i: adj[j]) {
            if (i != par) {
                childs[j].push_back(i);
                anc[i][0] = j;
                dfs(i,d+1,j);
            }
        }
    }
    
    DiTree() {
        numIncluded = 0;
        memset(dist,-1,sizeof(dist));
        memset(anc,-1,sizeof(anc));
        memset(isInclude,false,sizeof(isInclude));
        dfs(n,0,-1);
        //fill ancestor array
        for (int k = 1; k < maxk; k++) {
            for (int i = 1; i <= n; i++) {
                if (anc[i][k-1] != -1 && anc[anc[i][k-1]][k-1] != -1) {
                    anc[i][k] = anc[anc[i][k-1]][k-1];
                }
            }
        }
        isInclude[n] = true;
        numIncluded++;
    }

    void include(int i) {
        while (!isInclude[i]) {
            isInclude[i] = true;
            i = anc[i][0];
            numIncluded++;
        }
    }

    int numToInclude(int i) {
        if (isInclude[i]) return 0;
        int depth = dist[i];
        for (int kk = maxk - 1; kk >= 0; --kk) {
            if (anc[i][kk] != -1 && !isInclude[anc[i][kk]]) {
                i = anc[i][kk];
            }
        }
        return (depth - dist[i] + 1);
    }

    void solve() {
        int maxIncluded = n - k;
        for (int i = n - 1; i >= 1; i--) {
            int x = numToInclude(i);
            //cout << i << ' ' << x << ' ' << (n - numIncluded - x) << '\n';
            if (numIncluded + x <= maxIncluded) {
                include(i);
            }
        }
    }

    void test() {
        for (int i = 1; i <= n; i++) {
            for (int k = 0; k < maxk; k++) {
                cout << anc[i][k] << ' ';
            }
            cout << '\n';
        }
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    DiTree* tree = new DiTree();
  
    //output
    tree->solve();
    int numExcluded = 0;
    for (int i = 1; i <= n; i++) {
        if (!tree->isInclude[i]) {
            numExcluded++;
        }
    }
   
    //if (n == 76767) cout << n << ' ' << k << ' ' << tree->numIncluded << ' ' << numExcluded << '\n';

    for (int i = 1; i <= n; i++) {
        if (!tree->isInclude[i]) {
            cout << i << ' ';
        }
    }
    
    return 0;
}
	

