#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
bool a[maxn];
int n;

bool check(int x) {
    if (n/x == 2) return false;
    for (int i = 0; i < x; i++) {
        bool all = true;
        for (int j = i; j < n; j += x) {
            if (!a[j]) {
                all = false;
                break;
            }
        }
        if (all) return true;
    }
    return false;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    bool all = true;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (!a[i]) all = false;
    }
    if (all) {
        cout << "YES" << '\n';
        return 0;
    }
    for (int i = 2; i*i <= n; i++) {
        if (n % i == 0) {
            if (check(n/i)) {
                cout << "YES\n";
                return 0;
            }
            if (check(i)) {
                cout << "YES\n";
                return 0;
            }
        }
    }
    cout << "NO\n";

    return 0;
}

