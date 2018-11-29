#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

string s, t;
int oneCounter = 0;
int zeroCounter;
int zeroFirst, oneFirst;

int ctoi(char c) {return c-'a'+1;}
const int M = 1e9+7, b = 31;
ll pwr[1000005], inv[1000005];

ll modexp(ll x, ll n) {
    if (n == 0) return 1;
    if (n == 1) return x%M;
    if (n%2==0) return modexp((x*x)%M,n/2);
    return (x*modexp((x*x)%M,n/2))%M;
}

struct Hash
{
    int len = 0;
    ll hsh = 0;
    Hash() {}
    Hash(const string& s) {
        len = s.size();
        for (int i = s.size() - 1; i >= 0; i--) {
            int j = s.size() - i - 1;
            hsh = (hsh + pwr[j]*ctoi(s[i])) % M;
        }
    }
    void addHash(const Hash& h) {
        hsh = (hsh * pwr[h.len]) % M;
        hsh = (hsh + h.hsh) % M;
        len += h.len;
    }
};

ll prefix[1000005];

Hash orig;

Hash get(int i, int j) {
    Hash h;
    h.len = j;
    int a = t.size() - (i+j-1);
    int b = a + j - 1;
    h.hsh = (((prefix[b] - prefix[a-1] + M) % M) * inv[a-1]) % M;
    return h;
}

bool poss(int z_len) {
    int s_size = s.size();
    int t_size = t.size();
    int n_len = t_size - z_len * zeroCounter;
    if (n_len % oneCounter != 0) return false;
    n_len /= oneCounter;
    if (n_len == 0) return false;
    Hash h0 = get(zeroFirst*n_len,z_len);
    Hash h1 = get(oneFirst*z_len,n_len);
    /*
    cout << t.substr(zeroFirst*n_len,z_len) << ' ' << h0.hsh << ' ' << h0.len << '\n';
    cout << t.substr(oneFirst*z_len,n_len) << ' ' << h1.hsh << ' ' << h1.len << '\n';
    cout << '\n';
    */
    if (h0.hsh == h1.hsh) return false;
    Hash build;
    for (char c: s) {
        build.addHash(c=='0'?h0:h1);
        //cout << build.hsh << '\n';
    }
    //cout << orig.hsh << ' ' << build.hsh << "\n\n";
    return orig.hsh == build.hsh;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> s >> t;
    for (char c: s) if (c == '1') oneCounter++;
    if (oneCounter > s.size()/2) {
        for (char& c: s) {
            c = c=='0'?'1':'0';
        }
        zeroCounter = oneCounter;
        oneCounter = s.size() - zeroCounter;
        /*
        cout << "Ok check\n";
        for (char c: s) {
            cout << c;
        }
        cout << '\n';
        */
    }
    else {
        zeroCounter = s.size() - oneCounter;
    }
    for (int i = s.size() - 1; i >= 0; i--) {
        if (s[i] == '0') zeroFirst = i;
        else oneFirst = i;
    }
    pwr[0] = 1;
    for (int i = 1; i <= 1000000; i++) {
        pwr[i] = (pwr[i-1] * b) % M;
    }
    inv[0] = 1;
    inv[1] = modexp(b,M-2);
    for (int i = 2; i <= 1000000; i++) {
        inv[i] = (inv[i-1] * inv[1]) % M;
    }
    orig = Hash(t);
    for (int i = t.size() - 1; i >= 0; i--) {
        int j = t.size() - 1 - i;
        prefix[j+1] = (prefix[j] + pwr[j]*ctoi(t[i])) % M;
        //cout << j << ' ' << prefix[j+1] << '\n';
    }
    
    //now assume 0 is the most common occuring one
    int c = t.size() / zeroCounter;
    int ans = 0;
    for (int i = c; i >= 1; i--) {
        if (poss(i)) {
            //cout << "A: " << i << '\n';
            ans++;
        }
    }
    cout << ans << '\n';

    return 0;
}

