#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 105;
int parent[maxn]; //memset to -1
int Find(int x) {
    return parent[x] < 0 ? x : parent[x] = Find(parent[x]);
}

bool Union(int x, int y) {
    x = Find(x);
    y = Find(y);
    if (x == y) return false;
    if (parent[x] > parent[y]) swap(x,y);
    parent[x] += parent[y];
    parent[y] = x;
    return true;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    memset(parent,-1,sizeof parent);
    vector<pair<int,int>> a(n);
    for (int i = 0; i < n; i++) {
    	cin >> a[i].first >> a[i].second;
    }
    int comps = n;
    for (int i = 0; i < n; i++) {
    	for (int j = i + 1; j < n; j++) {
    		if (a[i].first == a[j].first || a[i].second == a[j].second) {
    			if (Union(i,j)) comps--;
    		}
    	}
    }

    cout << comps-1 << '\n';
    return 0;
}