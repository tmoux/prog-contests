#include <bits/stdc++.h>
using namespace std;
using ll = long long;


int main()
{
    int n, q; cin >> n >> q;
    cout << n << '\n';
    for (int i = 0; i < n; i++) {
        int r = rand() % n + 1;
        cout << r << ' ';
    }
    cout << '\n';
    cout << q << '\n';
    while (q--) {
        int t = rand() % 2 + 1;
        int l = rand() % n + 1;
        int r = rand() % n + 1;
        if (t == 1) {
            printf("%d %d %d\n",t,l,r);
        }
        else {
            int k = rand() % n + 1;
            printf("%d %d %d %d\n",t,l,r,k);
        }
    }

    return 0;
}

