#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pi = pair<int,int>;

const int maxn = 2e5+5;
int n, a[maxn], b[maxn], c[maxn], d[maxn];
int par[maxn], dist[maxn];

set<pi> S[maxn];

struct Node {
	int s, e, m;
	//covers s,e;
	set<pi> ys; //{y,id}
	Node *l, *r;
	
	Node(int a, int b) {
		s = a;
		e = b;
		if (s != e) {
			m = (s+e)/2;
			l = new Node(s,m);
			r = new Node(m+1,e);
			ys = l->ys;
			for (auto p: r->ys) {
				ys.insert(p);
			}
		}
		else {
			ys = S[s];
			l = NULL;
			r = NULL;
		}
	}

	void remove(int x, int y, int id) {
		if (s == e) {
			ys.erase({y,id});
			return;
		}
		if (x <= m) {
			l->remove(x,y,id);
		}
		else if (x > m) {
			r->remove(x,y,id);
		}
		ys.erase({y,id});
	}

	pi query(int st, int en) {
		if (st <= s && e <= en) {
			if (ys.empty()) return {2e9,-1};
			return *ys.begin();
		}
		pi ret = {2e9,-1};
		if (st <= m) {
			ret = min(ret,l->query(st,en));
		}
		if (en > m) {
			ret = min(ret,r->query(st,en));
		}
		return ret;
	}
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    vector<int> xs;
    for (int i = 1; i <= n; i++) {
    	cin >> a[i] >> b[i] >> c[i] >> d[i];
    	xs.push_back(a[i]); xs.push_back(c[i]);
    }
    sort(xs.begin(),xs.end());
    int pt = 0;
    map<int,int> compress;
    for (auto i: xs) if (!compress.count(i)) {
    	compress[i] = pt++;
    }
    for (int i = 1; i <= n; i++) {
    	S[compress[a[i]]].insert({b[i],i});
    }
    Node *root = new Node(0,pt);
    queue<int> q;
    q.push(0);
    while (!q.empty()) {
    	int i = q.front(); q.pop();
    	//cout << "node " << i << endl;
    	if (i == n) {
    		cout << dist[i] << '\n';
    		vector<int> v;
    		while (i != 0) {
    			v.push_back(i);
    			i = par[i];
    		}
    		reverse(v.begin(),v.end());
    		for (auto j: v) {
    			cout << j << ' ';
    		}
    		cout << '\n';
    		return 0;
    	}
    	int x = compress[c[i]];
    	//cout << "x = " << x << endl;
    	int y = d[i];
    	while (true) {
    		auto p = root->query(0,x);
    		if (p.first > y) break;
    		root->remove(compress[a[p.second]],b[p.second],p.second);
    		dist[p.second] = dist[i] + 1;
    		par[p.second] = i;
    		q.push(p.second);
    	}
    }
    cout << -1 << '\n';
}

