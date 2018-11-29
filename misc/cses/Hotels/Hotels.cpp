#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <set>
#include <list>
#include <map>
using namespace std;
typedef long long ll;
const int maxn = 200005;
int n, m, a[maxn];

int s[4*maxn], e[4*maxn], mx[4*maxn];
void build(int i, int l, int r) {
    s[i] = l, e[i] = r;
    if (l == r) {
        mx[i] = a[l];
        return;
    }
    int m = (l+r)/2;
    build(i*2,l,m);
    build(i*2+1,m+1,r);
    mx[i] = max(mx[i*2],mx[i*2+1]);
}

void change(int i, int idx, int x) {
    if (s[i] > idx || e[i] < idx) return;
    if (s[i] == idx && e[i] == idx) {
        mx[i] -= x;
        return;
    }
    change(i*2,idx,x);
    change(i*2+1,idx,x);
    mx[i] = max(mx[i*2],mx[i*2+1]);
}

int lowest(int i, int x) { //return lowest idx such that a[idx] >= x
    if (mx[i] < x) {
        //not possible
        return -1;
    }
    if (s[i] == e[i]) return s[i];
    if (mx[i*2] >= x) return lowest(i*2,x);
    return lowest(i*2+1,x);
}

int main()
{
	//ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
        cin >> a[i];
	}
    build(1,1,n);
	for (int i = 0; i < m; i++) {
        int ri; cin >> ri;
        int ans = lowest(1,ri);
        cout << (ans==-1?0:ans) << " \n"[i==m-1];
        if (ans != -1) {
            change(1,ans,ri);
        }
    }
	
	return 0;
}
