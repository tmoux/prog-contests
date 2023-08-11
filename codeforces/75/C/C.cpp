#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <map>
using namespace std;
typedef long long ll;

int g;
vector<int> factors;
map<int,int> primes;
vector<pair<int,int>> ps;
int gcd(int a, int b) {
    while (b) {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}

void getFactors(int i, int curr) {
    if (i == ps.size()) {
        factors.push_back(curr);
        return;
    }
    int mult = 1;
    for (int j = 0; j <= ps[i].second; j++) {
        getFactors(i+1,curr*mult);
        mult *= ps[i].first;
    }
}

void primeFactor(int n) {
    if (n == 1) return;
    for (int i = 2; i*i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0) {
                primes[i]++;
                n /= i;
            }
            primeFactor(n);
            return;
        }
    }
    //must be a prime
    primes[n]++;
}

int query(int l, int r) {
    auto it = upper_bound(factors.begin(),factors.end(),r);
    if (it == factors.begin()) {
        return -1;
    }
    --it;
    if (*it < l) return -1;
    return *it;
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    /*
    int a, b; cin >> a >> b;
    g = gcd(a,b);
    primeFactor(g);
    for (auto p: primes) {
        ps.push_back({p.first,p.second});
    }
    getFactors(0,1);
    sort(factors.begin(),factors.end());
    
    int n; cin >> n;
    while (n--) {
        int l, r; cin >> l >> r;
        cout << query(l,r) << '\n';
    }
    */
    

    return 0;
}
	

