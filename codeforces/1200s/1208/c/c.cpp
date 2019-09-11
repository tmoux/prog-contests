#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//0 4 8 12
//1 5 9 13
//2 6 10 14
//3 7 11 15
//
//

int grid[1005][1005];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    int pt = 0;
    for (int i = 0; i < n; i += 4) {
        for (int k = 0; k < n; k++) {
            for (int j = i; j < i+4; j++) {
                grid[j][k] = pt++;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << grid[i][j] << ' ';
        }
        cout << '\n';
    }
}

