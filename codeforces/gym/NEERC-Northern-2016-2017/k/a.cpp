#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Date
{
    int d, m, y;
    bool eq(const Date& rhs) {
        return d == rhs.d && m == rhs.m && y == rhs.y;
    }
    bool operator<(const Date& rhs) const {
        if (y != rhs.y) return y < rhs.y;
        if (m != rhs.m) return m < rhs.m;
        return d < rhs.d;
    }
};

int main() {
    freopen("king.in","r",stdin); freopen("king.out","w",stdout);
    int d, m, y; cin >> d >> m >> y;
    y -= 18;
    Date death = {d,m,y};
    Date best = {1,1,-10000};
    int id = -1;
    Date dd = {22,7,1995};
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        int d, m, y; cin >> d >> m >> y;
        Date dd = {d,m,y};
        if (death.eq(dd)) {
            cout << i+1 << '\n';
            return 0;
        }
        /*
        printf("%d %d %d\n",dd.d,dd.m,dd.y);
        cout << i << ": " << (dd < death) << '\n';
        */
        //cout << (best < dd) << '\n';
        if (dd < death) {
            if (best < dd) {
                best = {d,m,y};
                id = i+1;
            }
        }
    }
    cout << id << '\n';
}

