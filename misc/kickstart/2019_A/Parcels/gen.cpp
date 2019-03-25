#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    cout << t << '\n';
    while (t--) {
        cout << "10 10\n";
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                int t = rand() % 10;
                if (t == 0) cout << 1;
                else cout << 0;
            }
            cout << '\n';
        }
    }

}

