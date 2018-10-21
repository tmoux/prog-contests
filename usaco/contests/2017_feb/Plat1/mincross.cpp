/*
ID: silxikys
PROG: program
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <math.h>
#include <cstring>
using namespace std;

typedef long long ll;

class Node {
public:
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

	void add(int ind, int x) {
		sum += x;
		if (s == e) {
			return;
		}
		int m = (s+e)/2;
		if (ind <= m) {
			l->add(ind,x);
		}
		else {
			r->add(ind,x);
		}
	}

	int getsum(int st, int en) {
		//if completely included
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
const int maxn = 100005;
map<int,int> mp;
map<int,int> mp2;
int N, q[2][maxn], qInv[2][maxn], qCopy[2][maxn];

int main() 
{
    cin >> N;
    Node* root[2] = {new Node(0,N+1), new Node(0,N+1)};
    for (int seq = 0; seq < 2; seq++)
    for (int i = 1; i <= N; i++) {
        cin >> q[seq][i]; 
        qInv[seq][q[seq][i]] = i;
    }
    
    for (int seq = 0; seq < 2; seq++)
    for (int i = 1; i <= N; i++) {
        qCopy[seq][i] = qInv[1-seq][q[seq][i]];
    }

    for (int seq = 0; seq < 2; seq++) {
        for (int i = 1; i <= N; i++) {
            q[seq][i] = qCopy[seq][i];
        }
    }
    
    ll minans = 10000000000000LL;
    for (int seq = 0; seq < 2; seq++) {
        ll numInv = 0LL;
        for (int i = 1; i <= N; i++) {
            numInv += (ll)root[seq]->getsum(q[seq][i]+1,N);
            root[seq]->add(q[seq][i],1);
        }
        minans = min(minans,numInv);
        
        for (int i = N; i >= 1; i--) {
            numInv += 2 * qCopy[seq][i] - N - 1;
            minans = min(minans,numInv);
        }
    }

    cout << minans << '\n';

	return 0;
}

;

