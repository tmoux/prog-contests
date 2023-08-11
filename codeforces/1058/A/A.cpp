#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    bool is = false;
    for (int i = 0; i < n; i++) {
        bool ai; cin >> ai;
        is |= ai;
    }
    cout << (is ? "hard" : "easy") << '\n';

    return 0;
}

