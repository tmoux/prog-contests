#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 200005;

struct Node {
	int s, e, m;
	//coverse s,e;
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
		//push();
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

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; scanf("%d",&n);
    Node* root = new Node(0,maxn);
    int sz = 1;
    while (n--) {
        int t; scanf("%d",&t);
        switch (t) {
            case 1:
                int ai, xi; scanf("%d %d",&ai,&xi);
                root->add(1,ai,xi);
                break;
            case 2:
                int ki; scanf("%d",&ki);
                sz++;
                root->add(sz,sz,ki);
                break;
            case 3:
                int rem = root->getsum(sz,sz);            
                root->add(sz,sz,-rem);
                sz--;
                break;
        }
        ll tot = root->getsum(1,sz);
        double ans = (double)(tot)/sz;
        printf("%.10f\n",ans);
        //cout << fixed << setprecision(9) << ans << '\n';
    }

    return 0;
}
	

