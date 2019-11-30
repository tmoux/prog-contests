#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e6+6;
int n, k;

struct Node {
	int s, e, m;
	//covers s,e;
	int sum;
	Node *l, *r;
	
	Node(int a, int b) {
		s = a;
		e = b;
		sum = 0;
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
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    k = min(k,n-k);
    int cur = 0;
    ll ans = 1;
    Node *root = new Node(0,2*n+5);
    for (int i = 0; i < n; i++) {
        //cout << "cur = " << cur << '\n';
        int nxt = (cur+k);
        int add = root->getsum(cur+1,nxt-1) + 1;
        ans += add;
        cout << ans << ' ';
        root->add(cur,1);
        root->add(cur+n,1);
        root->add((nxt)%n,1);
        root->add((nxt)%n+n,1);
        //printf("added %d %d %d %d\n",cur,cur+n,(nxt)%n,(nxt)%n+n);
        cur = nxt%n;
    }
    cout << '\n';
}

