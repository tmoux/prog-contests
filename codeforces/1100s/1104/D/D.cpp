#include <bits/stdc++.h>
using namespace std;
using ll = long long;

char ask(int a, int b) {
    printf("? %d %d\n",a,b);
    fflush(stdout);
    char c;
    cin >> c;
    return c;
}

int solve() {
    int a = 1, b = 2;
    if (ask(0,1) == 'x') {
        return 1;
    }
    while (true) {
        if (ask(a,b) == 'y') {
            a = a * 2;
            b = b * 2;
        }
        else break;
    }
    int l = a, r = b;
    while (l + 1 < r) {
        int mid = (l+r)/2;
        if (ask(mid,r) == 'x') l = mid;
        else r = mid;
    }
    return r;
}

int main()
{
    while (true) {
        string s; cin >> s;
        assert(s != "mistake");
        if (s == "end") break;
        else {
            int ans = solve();
            printf("! %d\n",ans);
            fflush(stdout);
        }
    }

    return 0;
}

