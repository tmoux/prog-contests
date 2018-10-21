#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <set>
#include <map>
using namespace std;
typedef long long ll;

const int maxn = 100005;
int n, m, color[maxn];
vector<int> adj[maxn];

map<int,vector<int>> ctov;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> color[i];
        ctov[color[i]].push_back(i);
    }
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    int ans = 0;
    int mincolor = ctov.begin()->first;
    for (auto p: ctov) {
        int c = p.first;
        set<int> diffs;
        for (int i: p.second) {
            for (int j: adj[i]) {
                if (color[j] != c) {
                    diffs.insert(color[j]);
                }
            }
        }
        if (diffs.size() > ans) {
            ans = diffs.size();
            mincolor = c;
        }
    }

    cout << mincolor << '\n';

    return 0;
}
	

