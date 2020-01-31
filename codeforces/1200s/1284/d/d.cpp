#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n;
struct Invl
{
    int la, ra, lb, rb;
};

Invl a[maxn];

struct Node {
	int s, e, m;
	//covers s,e;
	int sum;
	int maxi;
    int mini;
	Node *l, *r;
	
	Node(int a, int b) {
		s = a;
		e = b;
		sum = 0;
		maxi = 0;
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

	void add(int i, int x) {
		if (s == e) {
			sum += x;
			maxi = sum;
            mini = sum;
			return;
		}
		if (i <= m) {
			l->add(i,x);
		}
		else if (i > m) {
			r->add(i,x);
		}
		else assert(false);
		sum = l->sum + r->sum;
		maxi = max(l->maxi,r->maxi);
		mini = min(l->mini,r->mini);
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

	int getmini(int st, int en) {
		if (st <= s && e <= en) {
			return mini;
		}
		int ret = 1e9+9;
		if (st <= m) {
			ret = min(ret,l->getmini(st,en));
		}
		if (en > m) {
			ret = min(ret,r->getmini(st,en));
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

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) {
        int la, ra, lb, rb; cin >> la >> ra >> lb >> rb;
        a[i] = {la,ra,lb,rb};
    }
    sort(a,a+n,[](auto a, auto b) {
            return a.la < b.la;
            });
    Node *left = new Node(0,n);
    Node *right = new Node(0,n);
    for (int i = 0; i < n; i++) {
        left->add(i,a[i].lb);
        right->add(i,a[i].rb);
    }
    bool poss = true;
    for (int i = 0; i < n; i++) {
        int l = i+1;
        if (l >= n || a[l].la > a[i].ra) continue;
        int r = l;
        for (int k = 17; k >= 0; k--) {
            int nr = r + (1<<k);
            if (nr < n && a[nr].la <= a[i].ra) {
                r = nr;
            }
        }
        if (right->getmini(l,r) < a[i].lb ||
            left->getmaxi(l,r) > a[i].rb) {
            /*
            printf("(%d %d), (%d %d)\n",a[i].la,a[i].ra,a[i].lb,a[i].rb);
            printf("l = %d, r = %d\n",l,r);
            cout << right->getmini(l,r) << '\n';
            cout << left->getmaxi(l,r) << '\n';
            */
            poss = false;
            break;
        }
    }

    for (int i = 0; i < n; i++) {
        swap(a[i].la,a[i].lb);
        swap(a[i].ra,a[i].rb);
    }

    sort(a,a+n,[](auto a, auto b) {
            return a.la < b.la;
            });
    left = new Node(0,n);
    right = new Node(0,n);
    for (int i = 0; i < n; i++) {
        left->add(i,a[i].lb);
        right->add(i,a[i].rb);
    }
    for (int i = 0; i < n; i++) {
        int l = i+1;
        if (l >= n || a[l].la > a[i].ra) continue;
        int r = l;
        for (int k = 17; k >= 0; k--) {
            int nr = r + (1<<k);
            if (nr < n && a[nr].la <= a[i].ra) {
                r = nr;
            }
        }
        if (right->getmini(l,r) < a[i].lb ||
            left->getmaxi(l,r) > a[i].rb) {
            /*
            printf("(%d %d), (%d %d)\n",a[i].la,a[i].ra,a[i].lb,a[i].rb);
            printf("l = %d, r = %d\n",l,r);
            cout << right->getmini(l,r) << '\n';
            cout << left->getmaxi(l,r) << '\n';
            */
            poss = false;
            break;
        }
    }

    cout << (poss ? "YES" : "NO") << '\n';
}

