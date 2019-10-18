#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n, k;
int a[maxn];
ll pre[maxn];

void addRight(int& l, int& r, ll& curr) {
    ll num = r-l+1;
    ll sum = pre[r] - pre[l-1];
    r++;
    ll add = 1LL*a[r]*num - sum;
    curr += add;
}

void moveLeft(int& l, int& r, ll& curr) {
    ll num = r-l;
    ll sum = pre[r] - pre[l];
    ll sub = sum - 1LL*a[l]*num;
    l++;
    curr -= sub;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    sort(a+1,a+n+1);
    for (int i = 1; i <= n; i++) {
        pre[i] = pre[i-1] + a[i];
    }
    int l = 1, r = 0;
    ll curr = 0;
    for (int i = 0; i < k; i++) {
        addRight(l,r,curr);
    }
    ll best = curr;
    for (int i = 0; i < n-k; i++) {
        addRight(l,r,curr);
        moveLeft(l,r,curr);
        best = min(best,curr);
    }
    cout << best << '\n';
}

