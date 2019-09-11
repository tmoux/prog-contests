#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    int odd = 0, even = 0;
    for (int i = 0; i < n; i++) {
        int ai; cin >> ai;
        if (ai % 2 == 0) {
            even++;
        }
        else {
            odd++;
        }
    }
    cout << min(odd,even) << '\n';
}

