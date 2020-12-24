#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int a[maxn];

struct Node {
	int s, e, m;
	//covers s,e;
  int mini;
	int maxi;
	Node *l, *r;
	
	Node(int a, int b) {
		s = a;
		e = b;
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

	void add(int i, ll x) {
		if (s == e) {
      mini = x;
			maxi = x;
			return;
		}
		if (i <= m) {
			l->add(i,x);
		}
		else if (i > m) {
			r->add(i,x);
		}
		else assert(false);
		mini = min(l->mini,r->mini);
		maxi = max(l->maxi,r->maxi);
	}

	int getmini(int st, int en) {
		if (st <= s && e <= en) {
			return mini;
		}
		int ret = 2e9;
		if (st <= m) {
			ret = min(ret,l->getmini(st,en));
		}
		if (en > m) {
			ret = min(ret,r->getmini(st,en));
		}
		return ret;
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
};

void solve() {
  int n; cin >> n;
  Node *root = new Node(0,n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    root->add(i,a[i]);
  }
  for (int i = 0; i < n-2; i++) {
    int X = root->getmaxi(0,i);
    int l1 = i, r1 = n;
    for (int k = 17; k >= 0; k--) {
      if (l1+(1<<k) < n && root->getmini(i+1,l1+(1<<k)) > X) l1 += 1<<k;
      if (r1-(1<<k) > i && root->getmini(i+1,r1-(1<<k)) < X) r1 -= 1<<k;
    }
    //cout << i << ": " << l1 << ' ' << r1 << endl;
    if (l1 == n-1 || root->getmini(i+1,l1+1) != X) continue;
    int l2 = i, r2 = n;
    for (int k = 17; k >= 0; k--) {
      if (l2+(1<<k) < n && root->getmaxi(l2+(1<<k),n-1) > X) l2 += 1<<k;
      if (r2-(1<<k) > i && root->getmaxi(r2-(1<<k),n-1) < X) r2 -= 1<<k;
    }
    //cout << "l2 " << i << ": " << l2 << ' ' << r2 << endl;
    if (l2 == n-1 || root->getmaxi(l2+1,n-1) != X) continue;
    int lidx = max(l1+1,l2+1-1);
    int ridx = min(r1-1,r2-1-1);
    if (lidx <= ridx) {
      int x = i+1;
      int y = (lidx)-(i+1)+1;
      int z = n-x-y;
      cout << "YES\n";
      //cout << lidx << ' '<< ridx << ": " << i << endl;
      cout << x << ' ' << y << ' ' << z << '\n';
      return;
    }
  }
  cout << "NO\n";
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) {
    solve();
  }
}

