#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;


struct Node {
	int s, e, m;
	//covers s,e;
	double sum;
	double lazy;
    double mult;
    //sum = sum*mult + lazy
	Node *l, *r;
	
	Node(int a, int b) {
		s = a;
		e = b;
		sum = 0;
		lazy = 0;
        mult = 1;
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
            l->mult *= mult;
			l->sum = l->sum*mult + (l->e - l->s + 1) * lazy;

			r->lazy += lazy;
            r->mult *= mult;
			r->sum = r->sum*mult + (r->e - r->s + 1) * lazy;
		}
		lazy = 0;
        mult = 1;
	}

	void add(int st, int en, double x) {
		//lazy: already accounted for in your own node, not the childs nodes
		if (st <= s && e <= en) {
			lazy += x;
			sum += (e - s + 1) * x;
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
	}

	void mul(int st, int en, double x) {
		//lazy: already accounted for in your own node, not the childs nodes
		if (st <= s && e <= en) {
			mult *= x;
			sum *= x;
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
	}

	double getsum(int st, int en) {
		push();
		//if completely included
		if (st <= s && e <= en) {
			return sum;
		}
		double ret = 0.0;
		if (st <= m) {
			ret += l->getsum(st,en);
		}
		if (en > m) {
			ret += r->getsum(st,en);
		}
		return ret;
	}
};

int n, q;
int a[maxn];

//[l1,r1] --> subtract expectation for each element by 
//sum(l1,r1)/(r1-l1+1)
//add sum(l2,r2)/(r2-l2+1)

int main() {
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cout << fixed << setprecision(10);
    cin >> n >> q;
    Node *root = new Node(1,n);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        root->add(i,i,a[i]);
    }
    while (q--) {
        int t; cin >> t;
        if (t == 1) {
            int l1, r1, l2, r2;
            cin >> l1 >> r1 >> l2 >> r2;
            double s1 = root->getsum(l1,r1)/(r1-l1+1);
            printf("avg val on [%d,%d]: %f\n",l1,r1,s1);
            //avg value of [l1,r1]
            double s2 = root->getsum(l2,r2)/(r2-l2+1);
            printf("avg val on [%d,%d]: %f\n",l2,r2,s2);
            //avg value of [l1,r1]
            //avg value of [l2,r2]
            root->add(l1,r1,(s2-s1)/(r1-l1+1));

            root->add(l2,r2,(s1-s2)/(r2-l2+1));

            cout << "curr array:\n";
            for (int i = 1; i <= n; i++) {
                cout << i << ": " << root->getsum(i,i) << '\n';
            }
        }
        else {
            int l, r; cin >> l >> r;
            /*
            cout << "curr array:\n";
            for (int i = 1; i <= n; i++) {
                cout << i << ": " << root->getsum(i,i) << '\n';
            }
            cout << '\n';
            */
            printf("[%d,%d]: %f\n",l,r,root->getsum(l,r));
            //cout << root->getsum(l,r) << '\n';
        }
    }
}

