#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n, q;
double a[maxn];

int main() {
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cout << fixed << setprecision(10);
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    while (q--) {
        int t; cin >> t;
        if (t == 1) {
            int l1, r1, l2, r2; cin >> l1 >> r1 >> l2 >> r2;
            double s1 = 0, s2 = 0;
            for (int i = l1; i <= r1; i++) {
                s1 += a[i];
                a[i] -= a[i]/(r1-l1+1);
            }
            for (int i = l2; i <= r2; i++) {
                s2 += a[i];
                a[i] -= a[i]/(r2-l2+1);
            }
            s1 /= (r1-l1+1)*(r2-l2+1);
            s2 /= (r2-l2+1)*(r1-l1+1);
            for (int i = l1; i <= r1; i++) {
                a[i] += s2;
            }
            for (int i = l2; i <= r2; i++) {
                a[i] += s1;
            }

            printf("[%d,%d],[%d,%d]\n",l1,r1,l2,r2);
            for (int i = 1; i <= n; i++) {
                cout << i << ": " << a[i] << '\n';
            }
        }
        else {
            int l, r; cin >> l >> r;
            double sum = 0;
            for (int i = l; i <= r; i++) {
                sum += a[i];
            }
            cout << sum << '\n';
        }
    }
}

