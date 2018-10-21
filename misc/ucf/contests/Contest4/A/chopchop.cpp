#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <set>
#include <map>
#include <cstring>
using namespace std;
typedef long long ll;

const int maxn = 100005;
int n, A[maxn], nxt[maxn], pre[maxn];

bool isUnique(int i, int l, int r) {
    //cout << "check1: " << (pre[i] < l) << '\n';
    //cout << "check2: " << (nxt[i] > r) << '\n';
    return ((pre[i] == 0 || pre[i] < l) && (nxt[i] == 0 || nxt[i] > r));
}

bool check(int l, int r) {
    //cout << l << ' ' << r << '\n';
    if (l > r) return true;
    if (l == r) return true;
    int ll = l, rr = r;
    while (ll <= rr) {
        //cout << ll << ' ' << rr << '\n';
        if (isUnique(ll,l,r)) {
            return (check(l,ll-1) && check(ll+1,r));
        }
        else if (isUnique(rr,l,r)) {
            return (check(l,rr-1) && check(rr+1,r));
        }
        ll++;
        rr--;
    }
    //cout << l << ' ' << r << '\n';
    return false;
}

bool solve() {
    map<int,int> p;
    memset(pre,0,sizeof(pre));
    memset(nxt,0,sizeof(nxt));
    for (int i = 1; i <= n; i++) {
        if (p.count(A[i]) == 0) {
            pre[i] = 0;
        }
        else {
            pre[i] = p[A[i]];
            nxt[p[A[i]]] = i;
        }
        p[A[i]] = i;
    }
    /*
    for (int i = 1; i <= n; i++) {
        cout << A[i] << ' ' << pre[i] << ' ' << nxt[i] << '\n';
    }
    */
    return check(1,n);    
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        memset(A,0,sizeof(A));
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> A[i];
        }
        cout << (solve() ? "1" : "0") << '\n';
    }
    
    /* 
    for (int i = 8; i <= 8; i++) {
        cout << i << ' ' << pre[i] << ' ' << nxt[i] << ' ' << isUnique(i,3,8) << '\n';
    }

    */
    return 0;
}
	

