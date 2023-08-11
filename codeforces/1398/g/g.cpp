#include <bits/stdc++.h>
using namespace std;
using ll = long long;

using cd = complex<double>;
const double PI = acos(-1);

/*
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
*/

//source: https://cp-algorithms.com/algebra/fft.html
void fft(vector<cd> & a, bool invert) {
    int n = a.size();

    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;

        if (i < j)
            swap(a[i], a[j]);
    }

    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            cd w(1);
            for (int j = 0; j < len / 2; j++) {
                cd u = a[i+j], v = a[i+j+len/2] * w;
                a[i+j] = u + v;
                a[i+j+len/2] = u - v;
                w *= wlen;
            }
        }
    }

    if (invert) {
        for (cd & x : a)
            x /= n;
    }
}

vector<int> multiply(vector<int> a, vector<int> b) {
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
    
    vector<int> res(n);
    for (int i = 0; i < n; i++) {
        res[i] = round(fa[i].real());
    }
    return res;
}

int N, X, Y, Q;
const int maxn = 200005, off = 200000;
vector<int> a, b, c;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> X >> Y;
    a.resize(maxn); b.resize(maxn);
    for (int i = 0; i <= N; i++) {
        int ai; cin >> ai;
        a[ai] = 1;
        b[off-ai] = 1;
    }
    c = multiply(a,b);
    cin >> Q;
    while (Q--) {
        int li; cin >> li;
        li /= 2;
        int ans = -1;
        for (int i = 1; i*i <= li; i++) {
            if (li%i) continue;
            for (int L: {li/i-Y,i-Y}) {
                if (L <= 0 || L+off >= c.size()) continue;
                if (c[L+off] != 0) {
                    ans = max(ans,2*(L+Y));
                }
            }
        }
        cout << ans << ' ';
    }
    cout << '\n';
}
