//Storing the graph
vector<int> g[maxn];
//Storing whether we have visited a node
bool vis[maxn];
//Storing the vertex matched to
int match[maxn];

bool hungarian(int u){
  for (int i = 0;i < g[u].size();++i){
    int v = g[u][i];
    if (!vis[v]){
			vis[v] = true;
			if (!match[v] || hungarian(match[v])){
				match[u] = v; match[v] = u; return true;
			}
		}
	}
	return false;
}
//in main: call hungarian for each vertex on one side
for (int i = 1;i <= nl;++i){
		memset(vis,false,sizeof vis);
		if (hungarian(i)) ans++; //if we can match i
}
