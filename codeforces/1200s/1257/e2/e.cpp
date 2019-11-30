#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int k[3];
//Don't be stubborn. If the judge says you are wrong, you are wrong.
//WA and believe in your idea and implementation?
//Approach the problem from another perspective.

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

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    for (int i = 0; i < 3; i++) {
        cin >> k[i];
    }
    vector<int> v;
    for (int i = 0; i < 3; i++) {
        vector<int> u;
        for (int j = 0; j < k[i]; j++) {
            int ai; cin >> ai;
            u.push_back(ai);
        }
        sort(u.begin(),u.end());
        for (int j: u) {
            v.push_back(j);
        }
    }
    Node *root = new Node(0,k[0]+k[1]+k[2]);
    int ans = 0;
    for (int i: v) {
        int t = root->getmaxi(0,i-1) + 1;
        root->add(i,t);
        ans = max(ans,t);
    }
    cout << k[0]+k[1]+k[2]-ans << '\n';
}

