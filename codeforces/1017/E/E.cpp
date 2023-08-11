#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <math.h>
using namespace std;
typedef long long ll;
const ll MAXN = 100005;
const double EPS = 1e-10;

struct Vertex
{
    ll x, y;
    
    Vertex() {
    }
    
    Vertex(ll x0, ll y0) : x(x0), y(y0) {
    }
    
    bool operator < (const Vertex &A) const
    {
        return x < A.x || (abs(x - A.x) <= EPS && y < A.y);
    }
    
    Vertex operator - (const Vertex &A)
    {
        return Vertex(x - A.x, y - A.y);
    }
    
}v[MAXN], ch[MAXN];

ll Cross(Vertex A, Vertex B)
{
    return A.x * B.y - A.y * B.x;
}

ll Dot(const Vertex& A, const Vertex& B) {
    return A.x * B.x + A.y * B.y;
}

ll Dist(Vertex A, Vertex B) {
    return (A.x-B.x)*(A.x-B.x) + (ll)(A.y-B.y)*(A.y-B.y);
}

ll n, m;

void solve(ll N, vector<Vertex>& vec) {
    for (ll i = 0; i < N; i++) {
        ll x, y; cin >> x >> y;
        v[i].x = x;
        v[i].y = y;
    }
    
    /*
    for (ll i = 0; i < N; i++) {
        cout << v[i].x << " " << v[i].y << endl;
    }
    */
    sort(v,v+N);
    ll m = 0;
    for (ll i = 0; i < N; ++i)
    {
        while (m > 1 && Cross(ch[m - 1] - ch[m - 2], v[i] - ch[m - 2]) <= 0) m--;
        ch[m++] = v[i];
    }
    ll k = m;
    for (ll i = N - 2; i >= 0; --i)
    {
        while (m > k && Cross(ch[m - 1] - ch[m - 2], v[i] - ch[m - 2]) <= 0) m--;
        ch[m++] = v[i];
    }
    ll ans = 0;
    ll j = m - 2;
    /*
    for (ll i = 0; i < m - 1; i++) {
        cout << ch[i].x << ' ' << ch[i].y << '\n';
    }
    */
    for (ll i = 0; i < m - 1; i++) {
        vec.push_back(ch[i]);
    }
}

const ll base = 1e8+7;
const ll M = 1e9+7;
ll inverse[MAXN];

ll modexp(ll x, ll n) {
    if (n == 0) return 1;
    if (n == 1) return x%M;
    if (n%2==0) return modexp((x*x)%M,n/2);
    return (x*modexp((x*x)%M,n/2))%M;
}

struct Hash
{
    ll len;
    ll* prefix;

    Hash(const vector<ll>& s) {
        len = s.size();
        prefix = new ll[4*MAXN];
        prefix[0] = 0LL;
        ll mult = 1;
        for (ll i = 0; i < s.size(); i++) {
            prefix[i+1] = (prefix[i] + (s[i]*mult)%M)%M;  
            mult = (mult*base)%M;
        }
    }

    ll sub(ll l, ll r) {
        //returns hash of [l,r] inclusive
        return ((prefix[r]-prefix[l-1]+M)*inverse[l-1])%M;
    }

    bool isSubstr(const Hash& other) {
        //checks if other is a substring of itself
        for (ll l = 1; l + other.len - 1 <= len; l++) {
            ll r = l + other.len - 1;
            if (other.prefix[other.len] == sub(l,r)) {
                return true;
            }
        }
        return false;
    }

    ~Hash() {
        delete[] prefix;
    }
};

int main() {
    cin >> n >> m;
    vector<Vertex> v1, v2;
    solve(n,v1);
    solve(m,v2);

    /*
    for (Vertex v: v1) {
        cout << v.x << ' ' << v.y << '\n';
    }
    cout << '\n';
    for (Vertex v: v2) {
        cout << v.x << ' ' << v.y << '\n';
    }
    */
    if (v1.size() != v2.size()) {
        cout << "NO" << '\n';
        return 0;
    }

    inverse[0] = 1;
    inverse[1] = modexp(base,M-2);
    for (ll i = 2; i < MAXN; i++) {
        inverse[i] = (inverse[i-1] * inverse[1]) % M;
    }
    vector<ll> h1, h2;
    ll vs = v1.size();
    for (ll i = 0; i < v1.size(); i++) {
        ll add = Dist(v1[i],v1[(i+1)%vs]) % base;
        ll cro = (Dot(v1[i] - v1[(i+1)%vs],v1[(i+2)%vs]-v1[(i+1)%vs])+base) % base;    
        while (cro < 0) cro += base;
        h1.push_back(add);
        h1.push_back(cro);
    }
    vs = v2.size();
    for (ll i = 0; i < v2.size(); i++) {
        ll add = Dist(v2[i],v2[(i+1)%vs]) % base;
        ll cro = (Dot(v2[i] - v2[(i+1)%vs],v2[(i+2)%vs]-v2[(i+1)%vs])+base) % base;    
        while (cro < 0) cro += base;
        h2.push_back(add);
        h2.push_back(cro);
    }
    auto old_count = h2.size();
    h2.resize(2*old_count);
    copy_n(h2.begin(),old_count,h2.begin()+old_count);

    /*
    for (ll i = 0; i < h1.size(); i += 2) {
        cout << h1[i] << ' ' << h1[i+1] << '\n';
    }
    cout << '\n';
    for (ll i = 0; i < h2.size(); i += 2) {
        cout << h2[i] << ' ' << h2[i+1] << '\n';
    }
    */
    //determine if hashes are substrings
    Hash hash1(h1), hash2(h2);
    if (hash2.isSubstr(h1)) {
        cout << "YES" << '\n';
    }
    else {
        cout << "NO" << '\n';
    }
	
	return 0;
}

