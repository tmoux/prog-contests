#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 2e5+5;
int n, m;
int a[maxn], b[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int ai; cin >> ai;
        a[ai] = i;
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
        b[i] = a[b[i]];    
    }

    while (m--) {
        int t; cin >> t;
        if (t == 2) {
            int x, y; cin >> x >> y;
            swap(b[x],b[y]);
        }
        else {
            int la, ra, lb, rb; cin >> la >> ra >> lb >> rb;
            if (rb-lb+1 <= n/2) {
                int ans = 0;
                for (int i = lb; i <= rb; i++) {
                    if (la <= b[i] && b[i] <= ra) {
                        ans++;
                    }
                }
                cout << ans << '\n';
            }
            else {
                int ans = ra-la+1;
                for (int i = lb - 1; i >= 1; i--) {
                    if (la <= b[i] && b[i] <= ra) {
                        ans--;
                    }
                }
                for (int i = rb + 1; i <= n; i++) {
                    if (la <= b[i] && b[i] <= ra) {
                        ans--;
                    }
                }
                cout << ans << '\n';
            }
        }
    }


    return 0;
}

