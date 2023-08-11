#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i, a, b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i, a) for (int i = (a)-1; i >= 0; i--)
#define trav(a, x) for (auto& a : x)

#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()

template<class T>
bool ckmin(T &a, const T &b) { return b < a ? a = b, 1 : 0; }

template<class T>
bool ckmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }

#define DEBUG(x) cerr << #x << ": " << x << '\n'

template<typename T>
ostream &operator<<(ostream &o, const vector<T> &v) {
    o << "[";
    for (auto it = v.begin(); it != v.end(); ++it) {
        o << *it;
        if (next(it) != v.end()) o << ", ";
    }
    o << "]";
    return o;
}

void fix(vector<int>& a, int n, vector<int>& ans) {
    if (n >= 3) {
        int x = n-1;
        int y = n-2;
        int pos_x = (int)distance(a.begin(), find(all(a), x));
        int pos_y = (int)distance(a.begin(), find(all(a), y));

        auto rev = [&](int p) {
            assert(p % 2 == 0);
            ans.push_back(p+1);
            reverse(a.begin(), a.begin()+p+1);
            pos_x = (int)distance(a.begin(), find(all(a), x));
            pos_y = (int)distance(a.begin(), find(all(a), y));
        };

        rev(pos_x);
        rev(pos_y-1);
        rev(n-1);
        rev(pos_x);
        rev(n-1);

        fix(a, n-2, ans);
    }
}

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& i: a) {
        cin >> i; i--;
    }
    for (int i = 0; i < n; i++) {
        if (i % 2 != a[i] % 2) {
            cout << -1 << '\n';
            return;
        }
    }
    vector<int> ans;
    fix(a, n, ans);
    //output
    cout << ans.size() << '\n';
    for (int i: ans) {
        cout << i << ' ';
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T; cin >> T;
    while (T--) solve();
}
