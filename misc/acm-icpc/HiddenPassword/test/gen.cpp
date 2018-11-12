#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t, n; cin >> t >> n;
    cout << t << '\n';
    while (t--) {
        cout << n << ' ';
        for (int i = 0; i < n; i++) {
            char c = (rand() % 26) + 'a';
            cout << c;
        }
        cout << '\n';
    }

    return 0;
}

