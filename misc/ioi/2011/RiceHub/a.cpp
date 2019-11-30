#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int N, L, x[maxn];
ll B;

bool check(int len) { //checking [i,i+len-1]
    int r = len-1;
    int median = len/2;
    ll curr = 0;
    for (int i = 0; i < len; i++) {
        curr += abs(x[i]-x[median]);
    }
    ll res = curr;
    for (int i = 1; i+len-1 < N; i++) {
        curr -= abs(x[i-1]-x[median]);
        median++;
        curr += 1LL*(median-i)*(x[median]-x[median-1]);
        curr -= 1LL*(i+len-1-median)*abs(x[median]-x[median-1]);
        curr += abs(x[i+len-1]-x[median]);        
        res = min(res,curr);
    }
    return res <= B;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> L >> B;
    for (int i = 0; i < N; i++) {
        cin >> x[i];
    }
    int lo = 0, hi = N+1;
    while (lo + 1 < hi) {
        int mid = (lo+hi)/2;
        if (check(mid)) {
            lo = mid;
        }
        else {
            hi = mid;
        }
    }
    cout << lo << '\n';
}

