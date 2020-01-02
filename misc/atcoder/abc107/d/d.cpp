#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n, a[maxn];
int pre[maxn];

int bit[3*maxn];
void add(int i, int x) {
    i += maxn;
    for (; i < 3*maxn; i += i & (-i))
        bit[i] += x;
}

int sum(int i) {
    i += maxn;
    int r = 0;
    for (; i; i -= i & (-i)) {
        r += bit[i];
    }
    return r;
}

ll cnt(int x) {
    for (int i = 1; i <= n; i++) {
        pre[i] = a[i] < x ? -1 : 1;
        pre[i] += pre[i-1];
    }
    memset(bit,0,sizeof bit);
    ll res = 0;
    add(0,1);
    for (int i = 1; i <= n; i++) {
        res += sum(2*maxn)-sum(pre[i]);    
        add(pre[i],1);
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    ll num = 1LL*n*(n+1)/4;
    int lo = 0, hi = 1e9+9;
    while (lo + 1 < hi) {
        int mid = (lo+hi)/2;
        //cout << mid << ": " << cnt(mid) << '\n';
        if (cnt(mid) <= num) lo = mid;
        else hi = mid;
    }
    cout << lo << '\n';
    /*
    cout << '\n';
    for (int i = hi-5; i <= hi+15; i++) {
        cout << i << ": " << cnt(i) << '\n';
    }
    */
}
