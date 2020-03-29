#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

const ld eps = 1e-9;
struct Line
{
    int x1, y1, x2, y2;
    ld m, b;
    void cv() {
        assert(x1 != x2);
        m = (ld)(y2-y1)/((ld)(x2-x1));
        b = -m*x1+y1;
    }
    ld eval(ld x) {
        return m*x+b;
    }
};

bool comp(ld x, ld y) {
    return abs(x-y) <= eps;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    Line l1, l2;
    cout << fixed << setprecision(10);
    cin >> l1.x1 >> l1.y1 >> l1.x2 >> l1.y2;
    cin >> l2.x1 >> l2.y1 >> l2.x2 >> l2.y2;
    if (l2.x1 == l2.x2) {
        swap(l1,l2);
    }
    if (l1.x1 == l1.x2) {
        if (l2.x1 == l2.x2) {
            if (l1.x2 == l2.x1) {
                cout << "coincident\n";
            }
            else {
                cout << "parallel\n";
            }
        }
        else {
            l2.cv();
            ld x = l1.x1;
            ld y = l2.eval(x);
            cout << x << ' ' << y << '\n';
        }
    }
    else {
        l1.cv();
        l2.cv();
        //cout << l1.m << ' ' << l2.m << endl;
        if (comp(l1.m,l2.m)) {
            if (comp(l1.b,l2.b)) {
                cout << "coincident\n";
            }
            else {
                cout << "parallel\n";
            }
        }
        else {
            ld x = (l2.b-l1.b)/(l1.m-l2.m);
            ld y = l1.eval(x);
            cout << x << ' ' << y << '\n';
        }
    }
}
