#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5, maxm = 42;
int n, m;
int c = 0;
map<string,int> mp;
bool adj[maxm][maxm];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    vector<set<int>> blocks;
    set<int> curr;
    for (int i = 0; i < n; i++) {
    	int t; cin >> t;
    	if (t == 1) {
    		blocks.push_back(curr);
    		curr = set<int>();
    	}
    	else {
    		string s; cin >> s;
    		int a;
    		if (mp.count(s)) a = mp[s];
    		else a = mp[s] = ++c;
    		curr.insert(a);
    	}
    }
    blocks.push_back(curr);
    for (set<int> s: blocks) {
    	for (int a: s) {
    		for (int b: s) {
    			if (a != b) adj[a][b] = true;
    		}
    	}
    }
    //find mis
    int ans = 0;
    vector<int> perm;
    for (int i = 1; i <= m; i++) perm.push_back(i);
    vector<int> chose;
    for (int i = 0; i < 100000; i++) {
    	chose.clear();
    	random_shuffle(perm.begin(),perm.end());
    	for (int d: perm) {
    		bool poss = 1;
    		for (int k = 0; k < chose.size(); k++) {
    			if (d == chose[k] || adj[d][chose[k]]) {
    				poss = false;
    				break;
    			}
    		}
    		if (poss) chose.push_back(d);
    	}
    	ans = max(ans,(int)(chose.size()));
    }
    cout << ans << '\n';

    return 0;
}