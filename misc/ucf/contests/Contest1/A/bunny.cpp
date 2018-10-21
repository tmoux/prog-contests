#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

const int N = 100005;
int n, q;
int y[N];

void add(int i, int d) {
    for (; i <= n; i += i&(-i)) {
        y[i] += d;
    }
}

// return x[1] + x[2] + ... + x[i]
int sum(int i) {
    int ans = 0;
    for (; i > 0; i -= i&(-i)) {
        ans += y[i];
    }
    return ans;
}

int query(int l, int r) {
    return sum(r) - sum(l-1);    
}

int base2(ll a) {
    if (a == 1) return 0;
    int res = -1;
    while (a) {
        a >>= 1;
        res++;
    }
    return res;
}

int compare(int a, int b) {
    if (a > b) return 1;
    if (b > a) return -1;
    else return 0;
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        ll ai; cin >> ai;
        add(i,base2(ai));
        //cout << i << ' ' << y[i] << '\n';
    }

    while (q--) {
        int t; cin >> t;
        if (t == 1) {
            //update
            ll x; int j;
            cin >> j >> x;
            int toAdd = base2(x);
            add(j,toAdd);
        }
        else {
            //range query
            int l1, r1, l2, r2;
            cin >> l1 >> r1 >> l2 >> r2;
            int a1 = query(l1,r1);
            int a2 = query(l2,r2);
            // cout << a1 << ' ' << a2 << '\n';
            cout << compare(a1,a2) << '\n';
        }
    }
    //cout << query(1,0,n,4,4) << '\n'; 

    return 0;
}
	

