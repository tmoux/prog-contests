#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 5e5+5;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    int x = 0, y = 0;
    while (n--) {
        char c; cin >> c;
        if (c == '+') {
            int a, b; cin >> a >> b;
            if (a < b) swap(a,b);
            x = max(a,x);
            y = max(b,y);
        }
        else {
            int a, b; cin >> a >> b;
            if (a < b) swap(a,b);
            bool is = (x <= a && y <= b);
            cout << (is ? "YES" : "NO") << '\n';
        }
    }

    return 0;
}

