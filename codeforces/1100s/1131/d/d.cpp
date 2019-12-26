#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1005;
int n, m;
char a[maxn][maxn]; 

int parent[2*maxn]; //memset to -1
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

int deg[2*maxn];
set<int> dir[2*maxn];

int ans[2*maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    memset(parent,-1,sizeof parent);
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
            int nj = j + n;
            if (a[i][j] == '=') {
                Union(i,nj);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int nj = j + n;
            int ii = Find(i);
            int jj = Find(nj);
            if (a[i][j] == '<') {
                dir[ii].insert(jj);
            }
            else if (a[i][j] == '>') {
                dir[jj].insert(ii);
            }
        }
    }
    for (int i = 0; i < n+m; i++) {
        for (int j: dir[i]) {
            //cout << i << " < " << j << endl;
            deg[j]++;
        }
    }
    queue<int> q;
    int num = 0;
    for (int i = 0; i < n+m; i++) {
        if (i == Find(i)) {
            if (deg[i] == 0) {
                q.push(i);
            }
            num++;
        }
    }
    int cnt = 0;
    while (!q.empty()) {
        int i = q.front(); q.pop();
        //cout << i << ": " << ans[i] << endl;
        cnt++;
        for (int j: dir[i]) {
            //cout << i << " < " << j << endl;
            ans[j] = max(ans[j],ans[i]+1);
            if (--deg[j] == 0) {
                q.push(j);
            }
        }
    }
    if (cnt < num) {
        cout << "No\n";
        return 0;
    }
    for (int i = 0; i < n+m; i++) {
        ans[i] = ans[Find(i)];
    }
    //output
    cout << "Yes\n";
    for (int i = 0; i < n; i++) {
        cout << ans[i]+1 << ' ';
    }
    cout << '\n';
    for (int i = n; i < n+m; i++) {
        cout << ans[i]+1 << ' ';
    }
    cout << '\n';
}

