#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 76;
bool grid[maxn][maxn];
bitset<maxn> g[maxn];
int n;
bool vis[maxn];
bitset<maxn> target;

bool check(vector<int>& v) {
    bitset<maxn> b;
    for (int i: v) {
        b |= g[i];
    }
    return b == target;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int tc = 1;
    random_device device;
    mt19937 gen(device());
    while (cin >> n) { 
        cout << "Case " << tc++ << ": ";
        memset(grid,0,sizeof grid);
        memset(vis,0,sizeof vis);
        target.reset();
        for (int i = 0; i < n; i++) {
            g[i].reset();
        }
        for (int i = 0; i < n; i++) {
            target[i] = 1;
            g[i].set(i);
            for (int j = 0; j < n; j++) {
                char c; cin >> c;
                grid[i][j] = c=='1';
                if (grid[i][j]) g[i].set(j);
            }
            //cout << i << ": " << g[i] << endl;
        }
        vector<int> v;
        while (true) {
            pair<int,int> mx = {-1,-1};
            for (int i = 0; i < n; i++) {
                if (vis[i]) continue;
                int deg = 1;
                for (int j = 0; j < n; j++) {
                    if (vis[j]) continue;
                    if (grid[i][j]) deg++;
                }
                mx = max(mx,{deg,i});
            }
            if (mx.first == -1) break;
            v.push_back(mx.second);
            vis[mx.second] = true;
            for (int j = 0; j < n; j++) {
                if (grid[mx.second][j]) vis[j] = true;
            }
        }
        //1
        vector<int> vv;
        for (int i = 0; i < n; i++) {
            vv = {i};
            if (v.size() > 1 && check(vv)) {
                v = vv;
                goto done;
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = i+1; j < n; j++) {
                vv = {i,j};
                if (v.size() > 2 && check(vv)) {
                    v = vv;
                    goto done;
                }
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = i+1; j < n; j++) {
                for (int k = j+1; k < n; k++) {
                    vv = {i,j,k};
                    if (v.size() > 3 && check(vv)) {
                        v = vv;
                        goto done;
                    }
                }
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = i+1; j < n; j++) {
                for (int k = j+1; k < n; k++) {
                    for (int l = k+1; l < n; l++) {
                        vv = {i,j,k,l};
                        if (v.size() > 4 && check(vv)) {
                            v = vv;
                            goto done;
                        }
                    }
                }
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = i+1; j < n; j++) {
                for (int k = j+1; k < n; k++) {
                    for (int l = k+1; l < n; l++) {
                        for (int m = l+1; m < n; m++) {
                            vv = {i,j,k,l,m};
                            if (v.size() > 5 && check(vv)) {
                                v = vv;
                                goto done;
                            }
                        }
                    }
                }
            }
        }
        //output
        done:
        cout << v.size() << ' ';
        for (auto i: v) {
            cout << i+1 << ' ';
        }
        cout << '\n';
    }
}
