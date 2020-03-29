#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n, k;
int a[maxn];

int ceil(int a, int b) {
    return (a+b-1)/b;
}
int calc(int diff, int m) {
    int lo = 0, hi = maxn;
    while (lo + 1 < hi) {
        int mid = (lo+hi)/2;
        if (ceil(diff,mid+1) <= m) {
            hi = mid;
        }
        else lo = mid;
    }
    return hi;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    for (int q = 1; q <= t; q++) {
        cout << "Case #" << q << ": ";
        cin >> n >> k;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        int lo = 0, hi = 1e9+9;
        while (lo + 1 < hi) {
            int mid = (lo+hi)/2;
            bool poss = true;
            int cnt = k;
            for (int i = 1; i < n; i++) {
                int diff = a[i]-a[i-1];
                if (diff <= mid) continue;
                int need = calc(diff,mid);
                if (cnt >= need) {
                    cnt -= need;
                }
                else poss = false;
            }
            if (poss) {
                hi = mid;
            }
            else lo = mid;
        }
        cout << hi << '\n';
    }
}

