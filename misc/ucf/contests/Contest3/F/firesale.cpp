#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

class Node {
public:
	int s, e, m;
	//coverse s,e;
	int sum;
	int maxi = 0, mini = 0;
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

	void add(int ind, int x) {
		sum += x;
		if (s == e) {
			maxi = sum;
            mini = sum;
			return;
		}
		int m = (s+e)/2;
		if (ind <= m) {
			l->add(ind,x);
		}
		else {
			r->add(ind,x);
		}
		maxi = max(l->maxi,r->maxi);
        mini = min(l->mini,r->mini);
	}

	int getmaxi(int st, int en) {
		//if completely included
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
		//if completely included
		if (st <= s && e <= en) {
			return mini;
		}
		int ret = 999999999;
		if (st <= m) {
			ret = min(ret,l->getmini(st,en));
		}
		if (en > m) {
			ret = min(ret,r->getmini(st,en));
		}
		return ret;
	}
};

int A[1000005];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, K; cin >> n >> K;
    Node* root = new Node(0,n-1);
    for (int i = 0; i < n; i++) {
        cin >> A[i];
        root->add(i,A[i]);
    }

    int maxans = 0;
    for (int i = 0; i < n; i++) {
        int j = 0;
        for (int k = 20; k >= 0; k--) {
            int posj = j + (1 << k);
            if (i + posj - 1 < n && (root->getmaxi(i,i+posj-1) - root->getmini(i,i+posj-1)) <= K) {
                j = posj;
            }
        }
        maxans = max(maxans,j);
        //cout << i << ' ' << i+j-1 << '\n';
    }
    cout << maxans << '\n';

    return 0;
}
	

