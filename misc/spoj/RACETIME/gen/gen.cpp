#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5, M = 1e9;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    freopen("out","w",stdout);
    cout << maxn << ' ' << maxn << '\n';
    for (int i = 1; i <= maxn; i++) {
        cout << (rand() % M) + 1 << '\n';
    }
    for (int i = 1; i <= maxn; i++) {
        int t = rand() % 2;
        if (t == 1) {
            cout << "C ";
            int l = (rand() % maxn) + 1, r = (rand() % maxn) + 1;
            if (l > r) swap(l,r);
            int x = (rand() % M) + 1;
            cout << l << ' ' << r << ' ' << x << '\n';
        }
        else {
            cout << "M ";
            int i = (rand() % maxn) + 1;
            int x = (rand() % M) + 1;
            cout << i << ' ' << x << '\n';
        }
    }

    return 0;
}
	

