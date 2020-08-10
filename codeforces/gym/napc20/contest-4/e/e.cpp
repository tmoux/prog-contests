#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define all(x) begin(x),end(x)

struct Node {
	int s, e, m;
	//covers s,e;
	int sum;
	int maxi;
	Node *l, *r;
	
	Node(int a, int b) {
		s = a;
		e = b;
		sum = 0;
		maxi = 0;
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

	void add(int i, int x) {
		if (s == e) {
			sum = x;
			maxi = sum;
			return;
		}
		if (i <= m) {
			l->add(i,x);
		}
		else if (i > m) {
			r->add(i,x);
		}
		sum = l->sum + r->sum;
		maxi = max(l->maxi,r->maxi);
	}

	int getmaxi(int st, int en) {
		if (st <= s && e <= en) {
			return maxi;
		}
		int ret = 0;
		if (st <= m) {
			ret = max(ret,l->getmaxi(st,en));
		}
		if (en > m) {
			ret = max(ret,r->getmaxi(st,en));
		}
		return ret;
	}	

	int getsum(int st, int en) {
		if (st <= s && e <= en) {
			return sum;
		}
		int ret = 0;
		if (st <= m) {
			ret += l->getsum(st,en);
		}
		if (en > m) {
			ret += r->getsum(st,en);
		}
		return ret;
	}
};

const int maxn = 1e6+6;
int n, q;

vector<pair<int,pair<int,int>>> begins; //{x,{y_min,y_max}}
struct Query
{
	int x1, x2, y1, y2, id;
};
bool ans[maxn];
vector<Query> queries;
int main() {
	scanf("%d %d\n",&n,&q);
	vector<int> xs;
	for (int i = 0; i < n; i++) {
		int x, y, r; scanf("%d %d %d",&x,&y,&r);
		y += 1e9;
		begins.push_back({x,{y-r,y+r}});
		xs.push_back(x);
	}
	for (int i = 0; i < q; i++) {
		int px, py, qx, qy, y_min, y_max;
		scanf("%d %d %d %d %d %d",&px,&py,&qx,&qy,&y_min,&y_max);
		y_min += 1e9;
		y_max += 1e9;
		queries.push_back({min(px,qx),max(px,qx),y_min,y_max,i});
		xs.push_back(px);
		xs.push_back(qx);
	}
	map<int,int> compress;
	int pt = 0;
	sort(all(xs));
	for (auto x: xs) {
		if (!compress.count(x)) compress[x] = pt++;
	}
	sort(all(begins),[](auto a, auto b) {
		return a.second.first > b.second.first;
	});
	sort(all(queries),[](auto a, auto b) {
		return a.y1 < b.y1;
	});
	Node *root = new Node(0,pt);
	for (Query qu: queries) {
		int x1 = compress[qu.x1];
		int x2 = compress[qu.x2];
		int y1 = qu.y1;
		int y2 = qu.y2;
		int id = qu.id;
		while (!begins.empty() && begins.back().second.first <= y1) {
			auto p = begins.back(); 
			begins.pop_back();
			int x = compress[p.first];
			int y = p.second.second;
			root->add(x,y);
		}
		ans[id] = root->getmaxi(x1,x2) < y2;
	}
	for (int i = 0; i < q; i++) {
		printf("%s\n",ans[i]?"YES":"NO");
	}
}