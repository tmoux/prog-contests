#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct CardboardBoxes
{
    ll count(ll S) {
        if (S % 2 != 0) {
            return 0;
        }
        S /= 2;
        ll res = 0;
        for (ll i = 1; i <= S; i++) {
            if (S % i == 0) {
                ll X = i;
                ll Y = S/i;
                //cout << X << ' ' << Y << endl;
                ll lb = 1;
                ll rb = min(X/2,Y-1);
                if (lb <= rb) {
                    res += rb-lb+1;
                }
                /*
                for (int a = 1; a <= X-a && a <= Y-1; a++) {
                    int b = X-a;
                    int c = Y-a;
                    assert(a >= 1 && b >= 1 && c >= 1);
                    res++;
                }
                */
            }
        }
        return res;
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    auto t = CardboardBoxes();
    int x; cin >> x;
    cout << t.count(x) << '\n';
}
