#include <bits/stdc++.h>
using namespace std;
using ll = long long;

using cd = complex<double>;
const double PI = acos(-1);

void fft(vector<cd>& a, bool invert) {
    int n = a.size();
    if (n == 1) return;

    vector<cd> a0(n/2), a1(n/2);
    for (int i = 0; 2*i < n; i++) {
        a0[i] = a[2*i];
        a1[i] = a[2*i+1];
    }
    fft(a0, invert);
    fft(a1, invert);

    double ang = 2*PI/n*(invert?-1:1);
    cd w(1), w_n(cos(ang),sin(ang));
    for (int i = 0; 2*i < n; i++) {
        a[i]     = a0[i] + w*a1[i];
        a[i+n/2] = a0[i] - w*a1[i];

        if (invert) { //divide by n in total
            a[i] /= 2;
            a[i+n/2] /= 2;
        }
        w *= w_n;
    }
}

vector<ll> multiply(vector<ll> a, vector<ll> b) {
    vector<cd> fa(a.begin(),a.end()), fb(b.begin(),b.end());
    int n = 1;
    while (n < a.size() + b.size()) n *= 2;
    fa.resize(n); fb.resize(n);

    fft(fa,false);
    fft(fb,false);
    for (int i = 0; i < n; i++) {
        fa[i] *= fb[i];
    }
    fft(fa,true);
    
    vector<ll> res(n);
    for (int i = 0; i < n; i++) {
        res[i] = round(fa[i].real());
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        string sa, sb; cin >> sa >> sb;
        vector<ll> a(sa.size()), b(sb.size());
        for (int i = sa.size()-1; i >= 0; i--) {
            a[sa.size()-1-i] = sa[i]-'0';
        }
        for (int i = sb.size()-1; i >= 0; i--) {
            b[sb.size()-1-i] = sb[i]-'0';
        }
        auto ans = multiply(a,b);
        int carry = 0;
        for (auto& j: ans) {
            j += carry;
            carry = j/10;
            j %= 10;
        }
        while (!ans.empty() && ans.back() == 0) ans.pop_back();
        if (ans.empty()) {
            cout << 0 << '\n';
        }
        else {
            reverse(ans.begin(),ans.end());
            /*
            for (auto j: ans) {
                cout << j;
            }
            cout << '\n';
            */
        }
    }
}
