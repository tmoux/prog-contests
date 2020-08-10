#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n;
vector<int> adj[maxn];
int take[maxn], skip[maxn];
void amax(int& a, int b) {
    a = max(a,b);
}

int ans = 0;

void dfs(int i, int p) {
    int c = adj[i].size() - (i!=p);
    for (int j: adj[i]) if (j != p) {
        dfs(j,i);
        amax(take[i],take[j]+c-1);
        amax(take[i],skip[j]+c);
        amax(skip[i],take[j]);
    }
    amax(ans,take[i]+(i!=p));
    if (c >= 2) {
        int mx = c-2;
        vector<int> v;
        for (int j: adj[i]) if (j != p) {
            v.push_back(max(skip[j]+1,take[j]));
        }
        sort(v.begin(),v.end(),greater<int>());
        mx += v[0] + v[1] + (i!=p);
        amax(ans,mx);

        int mx2 = 0;
        v.clear();
        for (int j: adj[i]) if (j != p) {
            v.push_back(take[j]);
        }
        sort(v.begin(),v.end(),greater<int>());
        mx2 += v[0] + v[1] + 1;
        amax(ans,mx2);
    }
    //cout << i << ": " << ans << endl;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n-1; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(1,1);
    cout << ans << '\n';
}

