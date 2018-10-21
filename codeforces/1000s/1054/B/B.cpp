#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    int c = 0;
    for (int i = 1; i <= n; i++) {
        int ai; cin >> ai;
        if (ai > c) {
            cout << i << '\n';
            return 0;
        }
        if (ai == c) c++;
    }
    cout << -1 << '\n';

    return 0;
}

