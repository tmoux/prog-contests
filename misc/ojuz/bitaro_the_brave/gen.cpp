#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    srand(time(0));
    int H = 3000, W = 3000;
    cout << H << ' ' << W << '\n';
    for (int i = 1; i <= H; i++) {
        for (int j = 1; j <= W; j++) {
            int r = rand() % 3;
            if (r == 0) cout << 'J';
            else if (r == 1) cout << 'O';
            else cout << 'I';
        }
        cout << '\n';
    }
}

