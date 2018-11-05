#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool seen[100000];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    cout << n << '\n';
    for (int i = 0; i < n; i++) {
        int r = (rand() % (2*n)) + 1;
        while (seen[r]) {
            r = (rand() % (2*n)) + 1;
        }
        seen[r] = true;
        cout << r << '\n';
    }

    return 0;
}

