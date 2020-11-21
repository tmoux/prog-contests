#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e4+4;
int n;
int ans[maxn];

int ask(int i, int j) {
    cout << "? " << i << ' ' << j << endl;
    int k; cin >> k;
    assert(k != -1);
    return k;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    int mx = 1;
    for (int i = 2; i <= n; i++) {
        int x = ask(i,mx);
        int y = ask(mx,i);
        if (x > y) {
            ans[i] = x;
            //cout << ":: " << x << endl;
        }
        else {
            ans[mx] = y;
            //cout << ":: " << y << endl;
            mx = i;
        }
    }
    ans[mx] = n;
    cout << "! ";
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << ' ';
    }
    cout << endl;
}
