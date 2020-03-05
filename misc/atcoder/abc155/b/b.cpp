#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    bool poss = true;
    for (int i = 0; i < n; i++) {
        int ai; cin >> ai;
        if (ai % 2 == 0) {
            if (ai % 3 == 0 || ai % 5 == 0) {
                continue;
            }
            else {
                poss = false;
                break;
            }
        }
    }
    cout << (poss ? "APPROVED" : "DENIED") << endl;
}

