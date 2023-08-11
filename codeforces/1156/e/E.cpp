#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, p[maxn], inv[maxn];

struct Node {
	int s, e, m;
	//covers s,e;
	ll sum;
	ll maxi;
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


	void add(int i, ll x) {
		if (s == e) {
			sum += x;
			maxi = sum;
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
	}

	ll getmaxi(int st, int en) {
		if (st <= s && e <= en) {
			return maxi;
		}
		ll ret = 0;
		if (st <= m) {
			ret = max(ret,l->getmaxi(st,en));
		}
		if (en > m) {
			ret = max(ret,r->getmaxi(st,en));
		}
		return ret;
	}	

	ll getsum(int st, int en) {
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

const int maxk = 17;
int gleft(Node *root, int i) {
    int mx = p[i];
    int l = i;
    for (int j = maxk; j >= 0; j--) {
        int nl = (l - (1<<j));
        if (nl < 1) continue;
        if (root->getmaxi(nl,i) <= mx) {
            l = nl;
        }
    }
    return l;
}

int gright(Node *root, int i) {
    int mx = p[i];
    int r = i;
    for (int j = maxk; j >= 0; j--) {
        int nr = (r + (1<<j));
        if (nr > n) continue;
        if (root->getmaxi(i,nr) <= mx) {
            r = nr;
        }
    }
    return r;
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    Node *root = new Node(1,n);
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
        inv[p[i]] = i;
        root->add(i,p[i]);
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        int l = gleft(root,i);
        int r = gright(root,i);
        //printf("%d: [%d,%d]\n",i,l,r);
        if (i-l < r-i) {
            for (int j = l; j < i; j++) {
                int pr = inv[p[i]-p[j]];
                if (i < pr && pr <= r) {
                    //printf("%d: a = %d, b = %d\n",p[i],p[j],p[i]-p[j]);
                    ans++;
                }
            }
        }
        else {
            for (int j = i + 1; j <= r; j++) {
                int pr = inv[p[i]-p[j]];
                if (l <= pr && pr < i) {
                    //printf("%d: a = %d, b = %d\n",p[i],p[j],p[i]-p[j]);
                    ans++;
                }
            }
        }
    }
    cout << ans << '\n';


    return 0;
}

