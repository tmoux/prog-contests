#include <bits/stdc++.h>
using namespace std;
using ll = long long;

bool curr[10];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        char c; cin >> c;
        if (c == 'L') {
            for (int i = 0; i < 10; i++) {
                if (!curr[i]) {
                    curr[i] = true;
                    break;
                }
            }
        }
        else if (c == 'R') {
            for (int i = 9; i >= 0; i--) {
                if (!curr[i]) {
                    curr[i] = true;
                    break;
                }
            }
        }
        else {
            int d = c - '0';
            curr[d] = false;
        }
    }
    for (int i = 0; i < 10; i++) {
        cout << curr[i];
    }
    cout << '\n';
}

