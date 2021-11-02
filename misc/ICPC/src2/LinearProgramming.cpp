/*solving linear programming with simplex algorithm.
Problem: Given the i-th condition to be \sum_{j=1}^n a_{ij}x_j \leq b_i
x_j \geq 0 (m conditions in total)
Find X-j that maximizes \sum_{j=1}^n c_jx_j*/
const double eps = 1e-8;
const double inf = 1e100;

double a[maxn][maxn], b[maxn], c[maxn], ans[maxn];
int id[maxn << 1];
int n, m; //n = num of variables; m = constraints

void pivot(int base,int base2){
	swap(id[base + n], id[base2]);
	for (int j = 0;j <= n;++j){
		if (j != base2){
			a[base][j] /= a[base][base2];
		}
	}
	a[base][base2] = 1 / a[base][base2];
	for (int i = 0;i <= m;++i){
		if (i != base && fabs(a[i][base2]) > eps){
			for (int j = 0;j <= n;++j){
				if (j != base2)
					a[i][j] -= a[base][j] * a[i][base2];
			}
			a[i][base2] *= -a[base][base2];
		}
	}
}

bool init(){
	for (int i = 1;i <= n + m;++i)
		id[i] = i;
	while (true){
		int x = 0, y = 0;
		double mini = 0;
		for (int i = 1;i <= m;++i){
			if (a[i][0] < mini - eps){
				x = i;
				mini = a[i][0];
			}
		}
		if (!x) break;
		for (int j = 1;j <= n;++j){
			if (a[x][j] < -eps) y = j;
		}
		if (!y) return false;
		pivot(x, y);
	}
	return true;
}

bool simplex(){
	while (true){
		int x = 0, y = 0;
		double mini = inf;
		for (int j = 1;j <= n;++j){
			if (a[0][j] > eps){
				y = j;
				break;
			}
		}
		if (!y) break;
		for (int i = 1;i <= m;++i){
			if (a[i][y] > eps && a[i][0] / a[i][y] < mini - eps){
				x = i;
				mini = a[i][0] / a[i][y];
			}
		}
		if (!x) return false;
		pivot(x, y);
	}
	return true;
}

//main program
for (int i = 1;i <= n;++i) a[0][i] = c[i];
for (int i = 1;i <= m;++i) a[i][0] = b[i];
if (!init()){
	printf("Infeasible\n");return 0;
}
else if (!simplex()){
	printf("Unbounded\n");return 0;
}
else{
	printf("%.10lf\n", -a[0][0]);
	for (int i = 1;i <= m;++i){
		if (id[n + i] <= n) ans[id[n + i]] = a[i][0];
	}
	if (t){
			for (int i = 1;i <= n;++i)  printf("%.10lf ", ans[i]);
			printf("\n");
		}
	}
	return 0;
}
