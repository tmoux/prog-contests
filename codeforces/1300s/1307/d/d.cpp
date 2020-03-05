#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, m, k;
int d1[maxn], dn[maxn];
vector<int> adj[maxn];
vector<int> a;

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
            sum = max(sum,x);
			return;
		}
		if (i <= m) {
			l->add(i,x);
		}
		else if (i > m) {
			r->add(i,x);
		}
		else assert(false);
        sum = max(l->sum,r->sum);
	}

	int getsum(int st, int en) {
		if (st <= s && e <= en) {
			return sum;
		}
		int ret = 0;
		if (st <= m) {
			ret = max(ret,l->getsum(st,en));
		}
		if (en > m) {
			ret = max(ret,r->getsum(st,en));
		}
		return ret;
	}
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m >> k;
    for (int i = 0; i < k; i++) {
        int ai; cin >> ai;
        a.push_back(ai);
    }
    for (int i = 0; i < m; i++) {
        int x, y; cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    memset(d1,-1,sizeof d1);
    memset(dn,-1,sizeof dn);
    queue<int> q;
    q.push(1);
    d1[1] = 0;
    while (!q.empty()) {
        int f = q.front(); q.pop();
        for (auto j: adj[f]) {
            if (d1[j] == -1) {
                d1[j] = d1[f] + 1;
                q.push(j);
            }
        }
    }
    q.push(n);
    dn[n] = 0;
    while (!q.empty()) {
        int f = q.front(); q.pop();
        for (auto j: adj[f]) {
            if (dn[j] == -1) {
                dn[j] = dn[f] + 1;
                q.push(j);
            }
        }
    }
    /*
    for (int i = 1; i <= n; i++) {
        cout << i << ": " << d1[i] << ' ' << dn[i] << endl;
    }
    */
    int ans = d1[n];
    int mx = 0;
    for (int qq: {0,1}) {
        reverse(a.begin(),a.end());
        Node *root = new Node(0,n);
        int mxSeen = 0;
        for (auto i: a) {
            int lo = 0, hi = n+5;
            //cout << i << ":\n";
            while (lo + 1 < hi) {
                int mid = (lo+hi)>>1;
                int t1 = mid-d1[i]-1, tn = mid-dn[i]-1;
                //cout << mid << ", " << t1 << ' ' << tn << endl;
                if (t1 <= mxSeen && t1 <= n && root->getsum(t1,n) >= tn) {
                    //cout << "max on range: " << root->getsum(t1,n) << endl;
                    lo = mid;
                }
                else hi = mid;
            }
            //cout << i << ": " << lo << endl;
            mx = max(mx,lo);
            root->add(dn[i],d1[i]);
            mxSeen = max(mxSeen,dn[i]);
        }
    }
    ans = min(ans,mx);
    cout << ans << endl;
}
