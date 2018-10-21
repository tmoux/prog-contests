#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
int k;
bool red[100000];
vector<int> adj[100000];
bool done[100000];
int sub[100000];
vector<int> cur;
int dfs1(int now, int from){
	sub[now] = 1;
	for(int i = 0; i<adj[now].size(); i++){
		int to = adj[now][i];
		if(done[to] || to==from){
			continue;
		}
		sub[now] += dfs1(to,now);
	}
	return sub[now];
}
void dfs2(int now, int from, int len){
	cur.push_back(len);
	for(int i = 0; i<adj[now].size(); i++){
		int to = adj[now][i];
		if(done[to] || to==from){
			continue;
		}
		dfs2(to,now,len+1);
	}
}
int findcent(int now, int from, int tot){
	for(int i = 0; i<adj[now].size(); i++){
		int to = adj[now][i];
		if(done[to] || to==from || sub[to]<=tot/2){
			continue;
		}
		return findcent(to,now,tot);
	}
	return now;
}
ll solve(vector<int> li){
	sort(li.begin(),li.end());
	int point = li.size();
	ll ret = 0LL;
	for(int i = 0; i<li.size(); i++){
		while(point>0 && li[point-1]+li[i]>k){
			point--;
		}
		if(point>i){
			ret += point - i - 1;
		}
	}
	return ret;
}
ll go(int now){
	ll ret = 0LL;
	dfs1(now,-1);
	now = findcent(now,-1,sub[now]);
	vector<int> all;
	all.push_back(0);
	//first = sum of lengths, second = # of paths
	for(int i = 0; i<adj[now].size(); i++){
		int to = adj[now][i];
		if(done[to]){
			continue;
		}
		cur.clear();
		dfs2(to,now,1LL);
		ret -= solve(cur);
		for(int j = 0; j<cur.size(); j++){
			all.push_back(cur[j]);
		}
	}
	ret += solve(all);
	done[now] = true;
	for(int i = 0; i<adj[now].size(); i++){
		int to = adj[now][i];
		if(done[to]){
			continue;
		}
		ret += go(to);
	}
	return ret;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int n;
	cin >> n >> k;
	bool vis[n];
	for(int i = 0; i<n; i++){
		string s;
		cin >> s;
		done[i] = false;
		red[i] = s=="G";
		vis[i] = false;
	}
	for(int i = 1; i<n; i++){
		int a, b;
		cin >> a >> b;
		a--;
		b--;
		if(red[a]!=red[b]){
			continue;
		}
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	ll ans = 0LL;
	for(int i = 0; i<n; i++){
		if(vis[i]){
			continue;
		}
		vector<int> li;
		li.push_back(i);
		for(int j = 0; j<li.size(); j++){
			int now = li[j];
			for(int k = 0; k<adj[now].size(); k++){
				int to = adj[now][k];
				if(!vis[to]){
					vis[to] = true;
					li.push_back(to);
				}
			}
		}
		ans += go(i);
	}
	cout << ans << endl;
}