#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5, maxk = 19;
int N, M;
vector<int> adj[maxn];
vector<pair<int,int>> dirs;

int pre = 0;
int preorder[maxn], postorder[maxn];
int parent[maxk][maxn];
int depth[maxn];
void root(int i, int p, int d) {
    depth[i] = d;
    parent[0][i] = p;
    preorder[i] = pre++;
    for (int j: adj[i]) {
        if (j == p) continue;
        root(j,i,d+1);
    }
    postorder[i] = pre-1;
}

int lca(int a, int b) {
    //returns x if a is direct ancestor of b and
    //-1 otherwise
    assert(a != b); //should never happen
    if (depth[b] <= depth[a]) return -1;    
    for (int k = maxk - 1; k >= 0; k--) {
        int bb = parent[k][b];
        if (bb != -1 && depth[bb] > depth[a]) b = bb;
    }
    if (parent[0][b] == a) return b;    
    else return -1;
}

struct Node {
	int s, e, m;
	//covers s,e;
	ll sum;
	ll lazy;
	ll mini;
	Node *l, *r;
	
	Node(int a, int b) {
		s = a;
		e = b;
		sum = 0;
		lazy = 0;
		mini = 0;
		if (s != e) {
			m = (s+e)/2;
			l = new Node(s,m);
			r = new Node(m+1,e);
		}
		else {
			l = NULL;
			r = NULL;
		}
	}

	void push() {
		if (s != e) {
			l->lazy += lazy;
			l->sum += (l->e - l->s + 1) * lazy;
			l->mini += lazy;

			r->lazy += lazy;
			r->sum += (r->e - r->s + 1) * lazy;
			r->mini += lazy;
		}
		lazy = 0;
	}

	void add(int st, int en, ll x) {
		//lazy: already accounted for in your own node, not the childs nodes
		if (st <= s && e <= en) {
			lazy += x;
			sum += (e - s + 1) * x;
			mini += x;
			return;
		}
		push();
		if (st <= m) {
			l->add(st,en,x);
		}
		if (en > m) {
			r->add(st,en,x);
		}
		sum = l->sum + r->sum;
		mini = min(l->mini,r->mini);
	}

	ll getsum(int st, int en) {
		push();
		//if completely included
		if (st <= s && e <= en) {
			return sum;
		}
		ll ret = 0;
		if (st <= m) {
			ret += l->getsum(st,en);
		}
		if (en > m) {
			ret += r->getsum(st,en);
		}
		return ret;
	}
};

int indegree[maxn], requires[maxn];
vector<int> req[maxn];
bool used[maxn];
bool poss() {
    queue<int> q; //list of valid nodes
    int taken = 0;
    for (int i = 1; i <= N; i++) {
        if (indegree[i] <= 1 && requires[i] == 0) {
            q.push(i);
            used[i] = true;
        }
    }
    while (!q.empty()) {
        taken++;
        int f = q.front(); q.pop();
        for (int j: adj[f]) {
            indegree[j]--;
        }
        for (int j: req[f]) {
            requires[j]--;
        }
        for (int j: adj[f]) {
            if (requires[j] == 0 && indegree[j] <= 1 && !used[j]) {
                q.push(j);
                used[j] = true;
            }
        }
        for (int j: req[f]) {
            if (requires[j] == 0 && indegree[j] <= 1 && !used[j]) {
                q.push(j);
                used[j] = true;
            }
        }
    }
    return taken == N;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    freopen("gathering.in","r",stdin); freopen("gathering.out","w",stdout);
    cin >> N >> M;
    for (int i = 0; i < N - 1; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
        indegree[a]++;
        indegree[b]++;
    }
    for (int i = 0; i < M; i++) {
        int a, b; cin >> a >> b;
        dirs.push_back({a,b});
        requires[b]++;
        req[a].push_back(b);
    }
    if (!poss()) {
        for (int i = 0; i < N; i++) {
            cout << 0 << '\n';
        }
        return 0;
    }
    //now we know it is possible
    memset(parent,-1,sizeof parent);
    root(1,-1,0);
    for (int k = 1; k < maxk; k++) {
        for (int i = 1; i <= N; i++) {
            if (parent[k-1][i] == -1) parent[k][i] = -1;
            else parent[k][i] = parent[k-1][parent[k-1][i]];
        }
    }

    Node *seg = new Node(0,N-1);
    for (auto& p: dirs) {
        int a = p.first;
        int b = p.second;
        //cout << a << ' ' << b << '\n';
        int lc = lca(a,b);
        if (lc != -1) {
            seg->add(preorder[lc],postorder[lc],1);
        }
        else {
            seg->add(preorder[1],postorder[1],1);
            seg->add(preorder[a],postorder[a],-1);
        }
    }

    for (int i = 1; i <= N; i++) {
        int x = seg->getsum(preorder[i],preorder[i]);
        cout << (x == M ? 1 : 0) << '\n';
    }
    
    /*
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (i != j) {
                cout << i << ' ' << j << ": " << lca(i,j) << '\n';
            }
        }
    }
    */

    return 0;
}

