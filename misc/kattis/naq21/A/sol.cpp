#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
using ld = long double;
 
#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
 
#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()
 
template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

ll to_ll(string s) {
    ll r = 0;
    ll mult = 1;
    for (int i = sz(s)-1; i >= 0; i--) {
        r += (s[i]-'0') * mult;
        mult *= 10;
    }
    return r;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    string s; cin >> s;
    ll n = to_ll(s);
    vector<bool> used(10, false);
    for (char c: s) used[c-'0'] = true;

    vector<int> digits;
    for (int d = 0; d <= 9; d++) {
        if (!used[d]) {
            digits.push_back(d);
        }
    }

    if (digits.empty()) {
        cout << "Impossible\n";
        return 0;
    }
    else if (sz(digits) == 1 && digits[0] == 0) {
        cout << 0 << '\n';
        return 0;
    }
    else {
        int leadingDigit = s[0]-'0';
        int len = sz(s);

        int smallest = digits[0];
        int smallestNonZero = digits[0] == 0 ? digits[1] : digits[0];
        int largest = digits.back();

        string larger;
        auto it = upper_bound(all(digits), leadingDigit);
        if (it != digits.end()) {
            larger += *it + '0';
            F0R(i, len-1) larger += smallest + '0';
        }
        else {
            larger += smallestNonZero + '0';
            F0R(i, len) larger += smallest + '0';
        }

        string smaller;
        it = lower_bound(all(digits), leadingDigit);
        if (it != digits.begin()) {
            smaller += *prev(it) + '0';
            F0R(i, len-1) smaller += largest + '0';
        }
        else {
            F0R(i, len-1) smaller += largest + '0';
        }

        ll largerD = to_ll(larger);
        ll smallerD = to_ll(smaller);

        // cout << "tst " << smallerD << ' ' << largerD << endl;

        if (largerD - n == n - smallerD) {
            cout << smallerD << ' ' << largerD << '\n';
        }
        else if (largerD - n < n - smallerD) {
            cout << largerD << '\n';
        }
        else {
            cout << smallerD << '\n';
        }
    }
}
