#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

struct Node
{
    int s, e, m;
    int sum;
    int mini;
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
        else {
            if (ind <= m) {
                l->add(ind,x);
            }
            else {
                r->add(ind,x);
            }
        }
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

int base2(ll x) {
    if (x == 1) return 0;
    x >>= 1;
    int ret = 0;
    while (x) {
        x >>= 1;
        ret++;
    }
    return ret;
}

int compare(int a, int b) {
    if (a > b) return 1;
    if (b > a) return -1;
    else return 0;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, q; cin >> n >> q;
    Node* root = new Node(0,n-1);
    for (int i = 0; i < n; i++) {
        ll x; cin >> x;
        root->add(i,base2(x));
    }
    while (q--) {
        int t; cin >> t;
        if (t == 1) {
            int j; ll x; cin >> j >> x;
            root->add(j-1,base2(x));
        }
        else {
            int l1, r1, l2, r2; cin >> l1 >> r1 >> l2 >> r2;
            cout << compare(root->getsum(l1-1,r1-1),root->getsum(l2-1,r2-1)) << '\n';  
        }
    }


    return 0;
}
	

