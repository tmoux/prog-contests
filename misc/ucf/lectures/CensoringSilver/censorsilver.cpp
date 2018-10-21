#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <deque>
using namespace std;
typedef long long ll;

const ll base = 29;
const ll M = 1e9+7;
string s, t;
ll badhash, bb;
ll inverse[1000005];
ll bexp[1000005];
ll prefix[1000005];

ofstream fout("censor.out");
ifstream fin("censor.in");

ll ctoi(char c) {
    return c - 'a' + 1;
}

ll modexp(ll x, ll n) {
    if (n == 0) return 1;
    if (n == 1) return x;
    if (n % 2 == 0) return modexp(x*x % M, n/2);
    else return (x * modexp(x*x % M,n/2)) % M;
}

ll strhash(const string& s) {
    ll mult = 1;
    ll res = 0;
    for (ll i = s.size() - 1; i >= 0; i--) {
        res = (res + mult * ctoi(s[i])) % M;     
        mult = (mult * base) % M;
    }
    return res;
}

ll addlast(ll hash, char c) {
    hash = (hash * base) % M;
    return (hash + ctoi(c)) % M;
}

ll poplast(ll hash, ll len) {
//pops last len
    hash = (hash + M - badhash) % M;
    hash = (hash * inverse[len]) % M;
    return hash;
}

ll addfirst(ll hash, char c, ll len) {
    hash = (hash + ctoi(c) * bexp[len]) % M; 
    return hash;
}

ll getHash(int l, int r) {
    return (prefix[r] + M - prefix[l-1] * bexp[r-l+1] % M) % M;
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> s >> t;
    badhash = strhash(t);
    bb = modexp(base,t.size()-1);
    inverse[1] = modexp(base,M-2);
    for (ll i = 2; i <= t.size(); i++) {
        inverse[i] = (inverse[i-1] * inverse[1]) % M;
    }
    bexp[0] = 1;
    bexp[1] = base;
    for (ll i = 2; i <= s.size(); i++) {
        bexp[i] = (bexp[i-1] * base) % M;
    }

    deque<char> deq;
    ll length = 0;
    for (ll i = 0; i < s.size(); i++) {
        length++;
        deq.push_back(s[i]);
        prefix[length] = addlast(prefix[length-1],s[i]);
        if (length - (int)t.size() >= 0) {
            ll subhash = getHash(length-t.size() + 1, length);
            if (subhash == badhash) {
                length -= t.size();
                for (ll a = 0; a < t.size(); a++) {
                    deq.pop_back();
                }
            }
        }
    }

    for (char c: deq) {
        //fout << c;
        cout << c;
    }
    //fout << '\n';
    cout << '\n';


    return 0;
}
	

