#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    const int maxn = 3e4, maxq = 2e5;
    cout << maxn << '\n';
    for (int i = 0; i < maxn; i++) cout << (rand() % 1000000000) << '\n';
    cout << maxq << '\n';
    for (int i = 0; i < maxq; i++) {
        int l = (rand()) % maxn, r = rand() % maxn;
        if (l > r) swap(l,r);
        cout << l << ' ' << r << '\n';
    }

    return 0;
}
	

