#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int M = 1e9+9;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    freopen("tmax","w",stdout);
    cout << 300000 << ' ' << 300000 << '\n';
    for (int i = 0; i < 300000; i++) {
        cout << (rand() % (M)) << ' ';
    }
    cout << '\n';
    for (int i = 0; i < 300000; i++) {
        int l = (rand() % 300000) + 1, r = (rand() % 300000) + 1;
        if (l > r) swap(l,r);
        cout << l << ' ' << r << '\n';
    }

    return 0;
}
	

