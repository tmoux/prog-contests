ll g[maxn][maxn];
ll fx[maxn], fy[maxn], a[maxn], b[maxn], slack[maxn],pre[maxn];
bool visx[maxn], visy[maxn];
int q[maxn];
int n;

void augment(int v){
	if (!v) return; fy[v] = pre[v]; augment(fx[pre[v]]); fx[fy[v]] = v;
}

void bfs(int source){
	memset(visx, 0, sizeof visx);
	memset(visy, 0, sizeof visy);
	memset(slack, 127, sizeof slack);
	int head, tail; head = tail = 1;
	q[tail] = source;
	while (true){
		while (head <= tail){
			int u = q[head++];
			visx[u] = true;
			for (int v = 1;v <= n;++v){
				if (!visy[v]){
					if (a[u] + b[v] == g[u][v])
					{
						visy[v] = true; pre[v] = u;
						if (!fy[v]){
							augment(v); return;
						}
						q[++tail] = fy[v];continue;
					}
					if (slack[v] > a[u] + b[v] - g[u][v]){
						slack[v] = a[u] + b[v] - g[u][v];
						pre[v] = u;
					}
				}
			}
		}
		ll d = inf;
		for (int i = 1;i <= n;++i){
			if (!visy[i]) d = min(d, slack[i]);
		}
		for (int i = 1;i <= n;++i){
			if (visx[i]) a[i] -= d;
			if (visy[i]) b[i] += d;
			else slack[i] -= d;
		}
		for (int v = 1;v <= n;++v){
			if (!visy[v] && !slack[v]){
				visy[v] = true;
				if (!fy[v]){
					augment(v);
					return;
				}
				q[++tail] = fy[v];
			}
		}
	}
}

ll km(){
	for (int i = 1;i <= n;++i){
		a[i] = -inf;
		b[i] = 0;
		for (int j = 1;j <= n;++j) a[i] = max(a[i], g[i][j]);
	}
	memset(fx, 0, sizeof fx);
	memset(fy, 0, sizeof fy);
	for (int i = 1;i <= n;++i) bfs(i);
	ll ans = 0;
	for (int i = 1;i <= n;++i) ans += a[i] + b[i];
	//vertex i on left is matched to g2[i][fx[i]] * fx[i]
	//g2[a][b]=1 iff exists edge ab
	return ans;
}
