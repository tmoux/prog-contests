#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Node {
	int s, e, m;
	//covers s,e;
	ll sum, cnt; //sum = sum of lengths, cnt = count of lengths
	Node *l, *r;
	
    Node() {};
	Node(int a, int b) {
		s = a;
		e = b;
		sum = 0;
        cnt = 0;
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

    void pull() {
        if (s == e) return;
        sum = l->sum + r->sum;
        cnt = l->cnt + r->cnt;
    }

	Node* add(int i, pair<ll,ll> p) {
		if (s == e) {
            Node *node = new Node(s,e);
            node->sum = sum + p.first;
            node->cnt = cnt + p.second;
			return node;
		}
        Node *node = new Node;
        node->s = s;
        node->e = e;
        node->m = (s+e)/2;
        node->sum = 0;
        node->cnt = 0;
		if (i <= m) {
			node->l = l->add(i,p);
            node->r = r;
		}
		else if (i > m) {
			node->r = r->add(i,p);
            node->l = l;
		}
        node->pull();
        /*
        cout << "created " << node->s << ' ' << node->e << endl;
        cout << (node->l->s) << ' ' << node->l->e << endl;
        cout << (node->r->s) << ' ' << node->r->e << endl;
        */
        return node;
	}

	ll getsum(int st, int en) {
        //cout << s << ' ' << e << endl;
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

	ll getcnt(int st, int en) {
		if (st <= s && e <= en) {
			return cnt;
		}
		ll ret = 0;
		if (st <= m) {
			ret += l->getcnt(st,en);
		}
		if (en > m) {
			ret += r->getcnt(st,en);
		}
		return ret;
	}
};

const int maxn = 1e5+5;
int N, Q;
struct Edge
{
    int to, color, wt;    
};

vector<Edge> adj[maxn];

const int maxk = 18;
int par[maxk][maxn];
int depth[maxn];
ll d[maxn];

void ROOT(int i, int p) {
    for (Edge& e: adj[i]) {
        if (e.to == p) continue;
        depth[e.to] = depth[i] + 1;
        par[0][e.to] = i;
        d[e.to] = d[i] + e.wt;
        for (int k = 1; k < maxk; k++) {
            par[k][e.to] = par[k-1][par[k-1][e.to]];
        }
        ROOT(e.to,i);
    }
}

int lca(int a, int b) {
    if (depth[a] > depth[b]) swap(a,b);
    for (int k = maxk - 1; k >= 0; k--) {
        int bb = par[k][b];
        if (bb != 0 && depth[bb] >= depth[a])
            b = bb;
    }
    if (a == b) return a;
    for (int k = maxk - 1; k >= 0; k--) {
        int aa = par[k][a];
        int bb = par[k][b];
        if (aa != bb) {
            a = aa;
            b = bb;
        }
    }
    return par[0][a];
}

ll dist(int a, int b) {
    int lc = lca(a,b);
    return d[a] + d[b] - 2*d[lc];
}

Node* roots[maxn];
void DFS(int i, int p) {
    for (Edge& e: adj[i]) {
        if (e.to == p) continue;
        roots[e.to] = roots[i]->add(e.color,{e.wt,1});
        DFS(e.to,i);
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> Q;
    for (int i = 0; i < N - 1; i++) {
        int a, b, c, d; cin >> a >> b >> c >> d;
        adj[a].push_back({b,c,d});
        adj[b].push_back({a,c,d});
    }
    ROOT(1,1);
    roots[1] = new Node(1,N);
    DFS(1,1);
    while (Q--) {
        int a, b, u, v; cin >> a >> b >> u >> v;
        ll curr = dist(u,v);
        int lc = lca(u,v);
        ll currColorLen = roots[u]->getsum(a,a) + roots[v]->getsum(a,a) - 2*roots[lc]->getsum(a,a);
        ll newColorLen = 1LL*b*(roots[u]->getcnt(a,a)+roots[v]->getcnt(a,a)-2*roots[lc]->getcnt(a,a));
        cout << (curr-currColorLen+newColorLen) << '\n';
    }
}

