#include <bits/stdc++.h>
using namespace std;
using ll = long long;

    
struct Node {
	int s, e, m;
	//covers s,e;
	ll sum;
	ll mini;
	Node *l, *r;
	
	Node(int a, int b) {
		s = a;
		e = b;
		sum = 0;
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

	void add(int i, ll x) {
		if (s == e) {
			sum += x;
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
		ll ret = 2e9;
		if (st <= m) {
			ret = min(ret,l->getmini(st,en));
		}
		if (en > m) {
			ret = min(ret,r->getmini(st,en));
		}
		return ret;
	}	
};

const int maxn = 250005;
int n;
int height[maxn];
int width[maxn];

map<int,int> previous;
int pre[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    Node *root = new Node(1,n);
    for (int i = 1; i <= n; i++) {
        cin >> width[i] >> height[i];
        root->add(i,height[i]);
        pre[i] = previous[height[i]];
        previous[height[i]] = i;
    }
    int ans = n;
    for (int i = 2; i <= n; i++) {
        int previousIndex = pre[i];
        if (previousIndex == 0) continue;
        int t = root->getmini(previousIndex,i-1);
        if (t == height[i]) {
            ans--;    
        }
    }
    cout << ans << '\n';
}

