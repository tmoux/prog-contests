#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e6+6;
int N;
pair<int,int> a[maxn];
int color[maxn]; //0 = uncolored, 1, 2
vector<int> adj[maxn];

bool intersect(pair<int,int> a, pair<int,int> b) {
    if (a.first > b.first) swap(a,b);
    return b.second < a.second || a.second < b.first;
}

bool fail = false;
void dfs(int i, int c) {
    color[i] = c;
    for (int j: adj[i]) {
        if (color[j] == c) {
            fail = true;
            return;
        }
        if (color[j] == 0) {
            dfs(j,c==1?2:1);
        }
    }
}


int main()
{
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> a[i].first >> a[i].second;
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j) continue;
            if (!intersect(a[i],a[j])) {
                adj[i].push_back(j);    
            }
        }
    }
    int comp = 0;
    for (int i = 0; i < N; i++) {
        if (color[i] == 0) {
            dfs(i,1);
            ++comp;
        }
    }
    if (fail) {
        cout << 0 << '\n';
    }
    else {
        int res = 1;
        for (int i = 0; i < comp; i++) {
            res = (res * 2) % 1000000007;
        }
        cout << res << '\n';
    }
}

