#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e4+4;
int n;
int a[maxn];
bool use[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]--;
    }
    int cur = 0;
    for (int i = n; i >= 2; i--) {
        int mov = a[cur] % i;
        while (mov > 0) {
            cur++;
            if (cur == n) cur = 0;
            if (!use[cur]) mov--;
        }
        use[cur] = true;
        while (true) {
            cur++;
            if (cur == n) cur = 0;
            if (!use[cur]) break;
        }
    }
    cout << (cur+1) << '\n';
}

