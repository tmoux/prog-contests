#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool subtract(int& n, int& eights) {
    int i = 10;
    while (i && n) {
        i--;
        n--;
    }
    while (i && eights) {
        i--;
        eights--;
    }
    return i == 0;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    string s; cin >> s;
    int eights = 0;
    for (char c: s) if (c == '8') eights++;
    int res = 0;
    n -= eights;
    while (eights) {
        eights--;
        if (subtract(n,eights)) {
            res++;
        }
        else break;
    }
    cout << res << '\n';


    return 0;
}

