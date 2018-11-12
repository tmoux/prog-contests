#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    cout << n << '\n';
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 50000; j++) {
            char c = (rand() % 240) + 1;
            cout << c;
        }
        cout << '\n';
    }

    return 0;
}

