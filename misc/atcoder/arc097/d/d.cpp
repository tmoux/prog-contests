#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int p[maxn];

vector<int>* par[maxn];
int N, M;

void init() {
    for (int i = 1; i <= N; i++) {
        par[i] = new vector<int>;
        par[i]->push_back(i);
    }
}

void Union(int a, int b) {
    auto pa = par[a], pb = par[b];
    if (pa == pb) return;
    if (pa->size() < pb->size()) {
        swap(pa,pb);
    }
    for (int i: *pb) {
        pa->push_back(i);
        par[i] = pa;
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        cin >> p[i];
    }
    init();
    while (M--) {
        int x, y; cin >> x >> y;
        Union(x,y);
    }
    set<vector<int>*> sets;
    int ans = 0;
    for (int i = 1; i <= N; i++) {
        if (sets.count(par[i])) continue;
        sets.insert(par[i]);
        set<int> indices;
        for (int j: *par[i]) {
            indices.insert(j);    
        }
        for (int j: *par[i]) {
            if (indices.count(p[j])) ans++;
        }
    }
    cout << ans << '\n';
}

