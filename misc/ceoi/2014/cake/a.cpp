#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
 * fast queries (few updates): 
 *      after each update, simply recompute all orders and 
 *      queries in O(1)
 *
 * fast updates (few queries):
 *      Give everyone enough space initally (5e5,2*5e5,3*5e5,...,10*5e5,10*5e5+1)
 *      Save each update, then before each query, recompute all orders and
 *      answer the query.
*/

const int maxn = 250005;
const int maxq = 5e5+5;
const ll INF = 1LL<<62;
int N, Q;
int d[maxn];
ll a[maxn];

struct Node {
	int s, e, m;
	//covers s,e;
	ll sum;
	ll mini;
	Node *l, *r;
	
	Node(int a, int b) {
		s = a;
		e = b;
		sum = INF;
		mini = INF;
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
			sum = x;
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
		mini = min(l->mini,r->mini);
	}

	ll getmini(int st, int en) {
		if (st <= s && e <= en) {
			return mini;
		}
		ll ret = INF;
		if (st <= m) {
			ret = min(ret,l->getmini(st,en));
		}
		if (en > m) {
			ret = min(ret,r->getmini(st,en));
		}
		return ret;
	}	
};

int start;
vector<int> v;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> start;
    vector<pair<int,int>> ps;
    for (int i = 1; i <= N; i++) {
        cin >> d[i];
        ps.push_back({d[i],i});
    }
    sort(ps.begin(),ps.end(),greater<pair<int,int>>());
    int t = 1;
    Node *root = new Node(1,N);
    for (auto p: ps) {
        a[p.second] = t;
        root->add(p.second,t);
        if (t <= 15) v.push_back(p.second);
        t++;
    }

    /*
    for (int i = 1; i <= N; i++) {
        cout << i << ": " << root->getmini(i,i) << '\n';
    }
    */

    cin >> Q;
    while (Q--) {
        char c; cin >> c;
        if (c == 'E') { //update
            int i, e; cin >> i >> e;
            e--;
            int curr = v[e];
            a[i] = a[curr]-1;
            root->add(i,a[i]);
            for (int j = 0; j < e; j++) {
                root->add(v[j],a[v[j]]-1); //decrement by 1
                a[v[j]]--;
            }

            auto it = find(v.begin(),v.end(),i);
            if (it != v.end()) v.erase(it);
            v.insert(v.begin()+e,i);
            if (v.size() > 15) v.pop_back();
            /*
            for (int i = 1; i <= N; i++) {
                cout << i << ": " << root->getmini(i,i) << '\n';
            }
            cout << '\n';
            */
        }
        else { //query
            int b; cin >> b;
            if (b == start) {
                cout << 0 << '\n';
            }
            else if (b < start) {
                int c = start+1;
                int mn = root->getmini(b,start-1);
                for (int k = 17; k >= 0; k--) {
                    int nc = c+(1<<k);
                    if (nc > N) continue;
                    if (root->getmini(start+1,nc) > mn) {
                        c = nc;
                    }
                }
                int d = root->getmini(start+1,c) > mn ? c : start;
                //cout << b << ' ' << d << '\n';
                cout << (d-b) << '\n';
            }
            else {
                int c = start-1;
                int mn = root->getmini(start+1,b);
                for (int k = 17; k >= 0; k--) {
                    int nc = c-(1<<k);
                    if (nc < 1) continue;
                    if (root->getmini(nc,start-1) > mn) {
                        c = nc;
                    }
                }
                int d = root->getmini(c,start-1) > mn ? c : start;
                //cout  << d << ' ' << b << '\n';
                cout << (b-d) << '\n';
            }
        }
    }
}
