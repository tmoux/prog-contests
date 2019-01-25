#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 5e5+5;
int N, M;

set<int> s[maxn];
struct Node {
	int s, e, m;
	//covers s,e;
	int mini;
	Node *l, *r;

	Node(int a, int b) {
		s = a;
		e = b;
		mini = maxn;
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

	pull() {
		mini = min(l->mini,r->mini);
	}

	void set(int i, int x) {
		if (s == e) {
			mini = x;
			return;
		}
		if (i <= m) {
			l->set(i,x);
		}
		else if (i > m) {
			r->set(i,x);
		}
		else assert(false);
		pull();
	}

	int getmini(int st, int en) {
		if (st <= s && e <= en) {
			return mini;
		}
		int ret = maxn;
		if (st <= m) {
			ret = min(ret,l->getmini(st,en));
		}
		if (en > m) {
			ret = min(ret,r->getmini(st,en));
		}
		return ret;
	}
};

int main()
{
    freopen("seating.in","r",stdin); 
	//freopen("seating.out","w",stdout);
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> M;	
	int ans = 0;
	Node *seg = new Node(1,N);
	while (M--) {
		char c; cin >> c;
		if (c == 'A') {
			int len; cin >> len;
			int idx = 
		}
		else {
			
		}
	}
		
		
	
		
		

    return 0;
}

