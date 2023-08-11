#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 5e5+5;
int n, k, d;
int a[maxn];

int bit[maxn];
void add(int i, int x) {
    for (; i <= n+10; i += i & (-i))
        bit[i] += x;
}

int sum(int i) {
    int r = 0;
    for (; i; i -= i & (-i)) {
        r += bit[i];
    }
    return r;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k >> d;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    sort(a+1,a+1+n);
    add(n+1,1);
    for (int i = n; i >= 1; i--) {
        int l = i+k-1;
        int lo = i, hi = n+1;
        while (lo + 1 < hi) {
            int mid = (lo+hi)/2;
            if (a[mid]-a[i] <= d) {
                lo = mid;
            }
            else hi = mid;
        }
        int r = lo;
        //cout << i << ": " << l << ' ' << r << '\n';
        if (l > r) {
            continue;
        }
        else {
            if (sum(r+1)-sum(l) > 0) {
                add(i,1);
            }
        }
        //cout << sum(i) << '\n';
    }
    cout << (sum(1) > 0 ? "YES" : "NO") << endl;
}
