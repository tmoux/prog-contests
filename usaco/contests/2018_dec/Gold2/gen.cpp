#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    cout << n << '\n';
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 5; j++) {
            int r = rand() % 1000000 + 1;
            cout << r << ' ';
        }
        cout << '\n';
    }

    return 0;
}

