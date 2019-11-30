#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n;
vector<int> a;

ll check(int x) {
    ll sum = 0;
    for (int i = 0; i < a.size(); i += x) {
        int mid = i+x/2;
        for (int j = i; j < i+x; j++) {
            sum += abs(a[j]-a[mid]);
        }
    }
    return sum;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    int tot = 0;
    for (int i = 0; i < n; i++) {
        int ai; cin >> ai;
        if (ai == 1) {
            tot++;
            a.push_back(i);
        }
    }
    ll ans = 1e18;
    for (int i = 1; i*i <= tot; i++) {
        if (tot % i == 0) {
            if (i > 1) ans = min(ans,check(i));
            if (tot/i > 1) ans = min(ans,check(tot/i));
        }
    }
    cout << (ans>=(ll)(1e18)?-1:ans) << '\n';
}

