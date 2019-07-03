#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5, MOD = 1e9+7;

int norm(ll x) {
        x %= MOD;
        while (x < 0) x += MOD;
        return x;
    }

template<int M>
struct Fraction
{
    int modexp(int a, int b) {
        int res = 1;
        while (b) {
            if (b&1) res = (1LL*a*res) % M;
            a = (1LL*a*a) % M;
            b >>= 1;
        }
        return res;
    }
    int inverse(int a) {
        return modexp(a,M-2);
    }
    

    ll num, den;
    Fraction(int a, int b) {
        num = a;
        den = b;
    }

    Fraction operator*(Fraction r) {
        return Fraction(norm(num*r.num),norm(den*r.den));
    }

    Fraction operator+(Fraction r) {
        return Fraction(norm(num*r.den+den*r.num),norm(den*r.den));
    }

    Fraction operator-() {
        return Fraction(norm(-num),den);
    }

    Fraction operator-(Fraction r) {
        return *this + (-r); 
    }

    ll eval() {
        return (1LL*num*inverse(den))%M;
    }
};
typedef Fraction<MOD> Frac;

int n, l[maxn], r[maxn];
ll isEqual[maxn], notEqual[maxn]; //probabilities that
//i is equal and not equal to previous element. 
//notEqual[i] = 1 - is[i] and notEqual[1] = 1;

Frac getProb(pair<int,int> a, pair<int,int> b) {
    pair<int,int> p = {min(a.first,b.first),max(a.second,b.second)};
    //cout << p.first << ' ' << p.second << '\n';
    int intersect = p.second-p.first+1;
    int N = a.second-a.first+1;
    int M = b.second-b.first+1;
    return Frac(intersect,1LL*N*M);
}

Frac getProb2(pair<int,int> a, pair<int,int> b, pair<int,int> c) {
    pair<int,int> p = {max(a.first,max(b.first,c.first)),min(a.second,min(b.second,c.second))};
    int intersect = p.second-p.first+1;
    int N = a.second-a.first+1;
    int M = b.second-b.first+1;
    int B = c.second-c.first+1;
    return Frac(intersect,norm(1LL*norm(N*M)*B));
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> l[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> r[i];
    }
    ll total = 0;
    for (int i = 1; i <= n; i++) {
        if (i == 1) {
            isEqual[i] = 0;
            notEqual[i] = 1;
        }
        else {
            isEqual[i] = getProb({l[i],r[i]},{l[i-1],r[i-1]}).eval();
            notEqual[i] = norm(1-isEqual[i]);
        }
        //cout << i << ": " << isEqual[i] << '\n';
        total = (total + notEqual[i]) % MOD;
    }
    cout << total << '\n';
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        total = norm(total - notEqual[i-1] - notEqual[i] - notEqual[i+1]);
        ans = norm(ans + norm(notEqual[i]*total));
        cout << norm(notEqual[i]*total) << '\n';
        ans = norm(ans + notEqual[i]);
        if (i > 1) ans = norm(ans + 1 - isEqual[i-1] - isEqual[i] + getProb2({l[i-2],r[i-2]},{l[i-1],r[i-1]},{l[i],r[i]}).eval());
        if (i < n) ans = norm(ans + 1 - isEqual[i] - isEqual[i+1] + getProb2({l[i-1],r[i-1]},{l[i],r[i]},{l[i+1],r[i+1]}).eval());
        total = norm(total + notEqual[i-1] + notEqual[i] + notEqual[i+1]);
        cout << i << ": " << ans << '\n';
    }
    cout << ans << '\n';
}

