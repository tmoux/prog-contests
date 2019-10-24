#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 2e5+5;
int n, a[N];

ll c(ll mid) {
    ll under = 0, over = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] <= mid) under += mid-a[i];
        else over += a[i]-mid;
    }
    return over + under;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i] -= i+1;
    }
    sort(a,a+n);
    int mid = a[n/2];
    cout << c(mid) << '\n';
}

