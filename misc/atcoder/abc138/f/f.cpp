#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll L, R;
const int M = 1e9+7;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> L >> R;
    for (int i = 1; i <= 50; i++) {
        for (int j = 1; j <= 50; j++) {
            if ((j^i) == (j%i)) {
                cout << i << ' ' << j << endl;
            }
        }
    }

}

