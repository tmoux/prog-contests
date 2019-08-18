#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n;
ll pre[4*maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    if (n == 1) {
        cout << "YES\n";
        cout << "1 2\n";
    }
    else if (n == 3) {
        cout << "YES\n";
        cout << "1 4 5 2 3 6\n";
    }
    else {
        if (n % 2 == 0) {
            cout << "NO\n";
        }
        else {
            cout << "YES\n";
            int l = 1, r = 2*n;
            for (int i = 1; i <= n; i++) {
                if (i % 2 == 1) {
                    pre[i] = l;
                    pre[i+n] = l+1;
                    l += 2;
                }
                else {
                    pre[i] = r;
                    pre[i+n] = r-1;
                    r -= 2;
                }
            }
            for (int i = 1; i <= 2*n; i++) {
                cout << pre[i] << ' ';
            }
            cout << '\n';
        }
    }
}

