#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int a[1005];
int N;
int calc(int K) {
    int res = 0;
    for (int i = 0; i < N; i++) {
        res += (a[i]^K);
    }
    return res;
}
void solve() {
    cin >> N;
    /*
    for (int i = 0; i < N; i++) {
        cin >> a[i];
    }
    */
    int sum = 0;
    cout << 1 << ' ' << (1<<20) << endl;
    cin >> sum;
    //sum = calc(1<<20);
    sum -= (1<<20)*N;
    int cursum = sum;
    vector<int> num1(20);
    for (int i = 0; i < 19; i++) {
        cout << 1 << ' ' << (1<<i) << endl;
        int x; cin >> x;
        //x = calc(1<<i);
        assert(x != -1);
        x = (sum-x)/(1<<i);
        num1[i] = (x+N)/2;
        cursum -= (1<<i)*num1[i];
    }
    num1[19] = cursum/(1<<19);
    int ans = 0;
    for (int i = 0; i < 20; i++) {
        if (num1[i]&1) ans += (1<<i);
    }
    cout << 2 << ' ' << ans << endl;
    int check; cin >> check;
    assert(check == 1);
    /*
    int realans = 0;
    for (int i = 0; i < N; i++) realans ^= a[i];
    cout << "real ans = " << realans << endl;
    */
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        solve();
    }
}
