#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 2e5+5;
int n, s, A[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> s;
    int med = n/2;
    for (int i = 0; i < n; i++) cin >> A[i];
    sort(A,A+n);
    ll res = 0;
    if (A[med] == s) {
        cout << 0 << '\n';
        return 0;
    }
    else if (A[med] < s) {
        for (int i = med; i < n; i++) {
            if (A[i] < s) {
                res += s - A[i];
            }
        }
        cout << res << '\n';
        return 0;
    }
    else {
        for (int i = med; i >= 0; i--) {
            if (A[i] > s) {
                res += A[i] - s;
            }
        }
        cout << res << '\n';
        return 0;
    }

    return 0;
}

