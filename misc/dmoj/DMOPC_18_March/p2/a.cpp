#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    bool hasT = false;
    bool hasU = false;
    for (int i = 0; i < n; i++) {
        char c; cin >> c;
        if (c == 'T') hasT = true;
        if (c == 'U') hasU = true;
        if (!(c == 'A' || c == 'C' || c == 'G' || c == 'T' || c == 'U')) {
            cout << "neither\n";
            return 0;
        }
    }
    if (!hasT && !hasU) {
        cout << "both\n";
    }
    else if (hasT && hasU) {
        cout << "neither\n";
    }
    else if (hasT && !hasU) {
        cout << "DNA\n";
    }
    else {
        cout << "RNA\n";
    }
}

