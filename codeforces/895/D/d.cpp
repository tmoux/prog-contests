#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e6+6, M = 1e9+7;
int mult(int a, int b) {
    return (1LL*a*b) % M;
}
int modexp(int a, int b) {
    int res = 1;
    while (b > 0) {
        if (b&1) res = mult(res,a);
        a = mult(a,a);
        b >>= 1;
    }
    return res;
}
int inverse(int a) {
    return modexp(a,M-2);
}

int n;
int fac[maxn], ifac[maxn];
int inv[maxn];

void madd(int& a, int b) {
    a += b;
    if (a > M) a -= M;
}

int mp[26];
int f(const string& a, const string& b) { //# of ways to permute a s.t. a < b
    memset(mp,0,sizeof mp);
    for (char c: a) mp[c-'a']++;
    int div = 1;
    for (int i = 0; i < 26; i++) {
        div = mult(div,ifac[mp[i]]);
    }
    int sum = 0;
    for (int i = 0, num = a.size()-1; i < a.size(); i++, num--) {
        for (int c = 0; c < 26; c++) {
            char pf = c + 'a';
            int ps = mp[c];
            if (ps == 0) continue;
            if (pf < b[i]) {
                div = mult(div,fac[ps]);
                div = mult(div,ifac[ps-1]);
                int add = mult(fac[num],div);
                madd(sum,add);
                div = mult(div,fac[ps-1]);
                div = mult(div,ifac[ps]);
            }
        }
        if (mp[b[i]-'a'] == 0) {
             break;
        }
        div = mult(div,mp[b[i]-'a']);
        --mp[b[i]-'a'];
    }
    return sum;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    string a, b;
    cin >> a >> b;
    fac[0] = 1;
    for (int i = 1; i <= a.size(); i++) {
        fac[i] = mult(fac[i-1],i);
    }
    for (int i = 0; i <= a.size(); i++) {
        ifac[i] = inverse(fac[i]);
    }
    for (int i = 1; i <= a.size(); i++) {
        inv[i] = inverse(i);
    }
    int ans = (((f(a,b) - f(a,a) - 1 + M) % M) + M) % M;
    cout << ans << '\n';
    return 0;
}
