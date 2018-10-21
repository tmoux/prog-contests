#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 2005;
int n, m;
vector<int> adj[maxn];
int type[maxn];

inline int other(int i) {return i == 1 ? 2 : 1;}

void solve(int test) {
	bool works = true;
	for (int i = 1; i <= n && works; i++) {
		if (type[i] == 0) {
			queue<int> q;
			q.push(i);
			type[i] = 1;
			while (!q.empty()) {
				int f = q.front();
				for (int j: adj[f]) {
					if (type[j] == other(type[f])) continue;
					else if (type[j] == 0) {
						q.push(j);
						type[j] = other(type[f]);
					}
					else {
						works = false;
						break;
					}
				}
				q.pop();
			}
		}
	}
	/*
	for (int i = 1; i <= n; i++) {
		cout << type[i] << '\n';
	}
	*/
	printf("Scenario #%d:\n",test);
	printf("%s bugs found!\n",works ? "No suspicious" : "Suspicious");
}

int main()
{
    #ifdef OFFLINE
    freopen("in","r",stdin);
    #endif
    int t; scanf("%d",&t);
    for (int a = 1; a <= t; a++) {
    	scanf("%d %d",&n,&m);
    	memset(type,0,sizeof type);
    	for (int i = 1; i <= n; i++) adj[i].clear();
    	for (int i = 0; i < m; i++) {
    		int u, v; scanf("%d %d",&u,&v);
    		adj[u].push_back(v);
    		adj[v].push_back(u);
    	}
    	solve(a);
    }


    return 0;
}