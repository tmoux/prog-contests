#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int a, b, c, d; cin >> a >> b >> c >> d;
    set<int> s;
    for (int i = 0; i < 100000; i++) {
        s.insert(b+i*a);
    }
    for (int i = 0; i < 100000; i++) {
        if (s.count(d+i*c)) {
            cout << (d+i*c) << '\n';
            return 0;
        }
    }
    cout << -1 << '\n';

    return 0;
}

