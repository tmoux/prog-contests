#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, q;
int a[maxn];

const ll INV = -1; //invalid number for lazy
struct Node {
	int s, e, m;
	//covers s,e;
	ll sum;
  ll mini;
	ll lazy;
	Node *l, *r;
	
	Node(int a, int b) {
		s = a;
		e = b;
		sum = 0;
    mini = 0;
		lazy = INV;
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
		if (lazy == INV) return;
		if (s != e) {
			l->lazy = lazy;
			l->sum = (l->e - l->s + 1) * lazy;
      l->mini = lazy;

			r->lazy = lazy;
			r->sum = (r->e - r->s + 1) * lazy;
      r->mini = lazy;
		}
		lazy = INV;
	}

	void pull() {
		sum = l->sum + r->sum;
    mini = min(l->mini,r->mini);
	}

	void add(int st, int en, ll x) {
		//lazy: already accounted for in your own node, not the childs nodes
		if (st <= s && e <= en) {
			lazy = x;
      mini = x;
			sum = (e - s + 1) * x;
			return;
		}
		push();
		if (st <= m) {
			l->add(st,en,x);
		}
		if (en > m) {
			r->add(st,en,x);
		}
		pull();
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

  int getMinIdx(ll y) {
    push();
    //cout << "minidx " << s << ' ' << e << ": " << y << endl;
    if (s == e) {
      return mini <= y ? s : n+1;
    }
    if (l->mini <= y) {
      return l->getMinIdx(y);
    }
    else {
      return r->getMinIdx(y);
    }
  }
  int walk(ll z) {
    push();
    if (s == e) return sum <= z ? s : s-1;
    //cout << s << ' ' << e << ": " << z << " -- " << l->sum+r->mini << '\n';
    if (l->sum+r->mini > z) {
      return l->walk(z);
    }
    else {
      return r->walk(z-(l->sum));
    }
  }
};

int main() {
  scanf("%d %d",&n,&q);
  Node *root = new Node(1,n);
  for (int i = 1; i <= n; i++) {
    scanf("%d",a+i);
    root->add(i,i,a[i]);
  }
  while (q--) {
    int t, x, y; 
    scanf("%d %d %d",&t,&x,&y);
    if (t == 1) {
      int i = root->getMinIdx(y);
      if (i <= x) root->add(i,x,y);
      /*
      cout << "setting " << i << ' ' << x << '\n';
      for (int i = 1; i <= n; i++) {
        cout << root->getsum(i,i) << ' ';
      }
      cout << '\n';
      */
    }
    else {
      int ans = 0;
      while (x <= n) {
        ll sum = x==1?0:root->getsum(1,x-1);
        //largest idx where sum is <= sum+y
        int i = root->walk(sum+y);
        //cout << x << ' ' << i << ": " << y << ' ' << root->getsum(x,i) << '\n';
        ans += i-x+1;

        y -= root->getsum(x,i);
        x = max(i+1,root->getMinIdx(y));
        //cout << "x = " << x << endl;
      }
      printf("%d\n",ans);
    }
  }
}
