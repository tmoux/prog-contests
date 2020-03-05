#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n;
int a[maxn];
vector<int> neg, zero, pos;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    ll k; cin >> k;    
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a,a+n);
    ll lo = -1e18-5, hi = 1e18+5;
    while (lo + 1 < hi) {
        ll mid = (lo+hi)/2;
        ll cnt = 0;
        for (int i = 0; i < n; i++) {

        }
    }
}
