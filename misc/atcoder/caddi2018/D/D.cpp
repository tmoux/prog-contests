#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    int r = 0;
    for (int i = 0; i < n; i++) {
        int a; cin >> a;
        r ^= a;
    }
    cout << (r&1 ? "first" : "second") << '\n';

    return 0;
}

