#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 3e5+5;
int n;
ll bit[maxn], a[maxn];

void add(int i, int x) {
    for (; i <= n; i += i&(-i)) {
        bit[i] += x;    
    }
}
ll sum(int x) {
    ll res = 0;
    for (; x; x -= x&(-x)) {
        res += bit[x];
    }
    return res;
}
void addRange(int l, int r, int x) {
    add(l,x);
    add(r+1,-x);
}

void primeFactor(int n, map<int,int>& primes) {
	if (n == 1) return;
	for (int i = 2; i*i <= n; i++) {
		if (n % i == 0) {
			while (n % i == 0) {
				primes[i]++;
				n /= i;
			}
			primeFactor(n,primes);
			return;
		}
	}
	primes[n]++;
}

vector<int> facs[maxn];

void fillFac(vector<pair<int,int>> primes, int curr, int i, int x) {
    if (i == primes.size()) {
        facs[x].push_back(curr);
        return;
    }
    pair<int,int> p = primes[i];
    int mult = 1;
    for (int j = 0; j <= p.second; j++) {
        fillFac(primes,curr*mult,i+1,x);   
        mult *= p.first;
    }
}

ll get(int i) {
    if (facs[i].empty()) {
        map<int,int> primes;
        primeFactor(i,primes);
        vector<pair<int,int>> ps;
        for (auto& p: primes) ps.push_back(p);
        fillFac(ps,1,0,i);
    }
    ll res = 0;
    for (int j: facs[i]) {
        res += sum(j);
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    int q; cin >> q;
    while (q--) {
        int t; cin >> t;
        if (t == 1) {
            int i; cin >> i;
            ll ans = get(i) + a[i];
            cout << ans << '\n';
        }
        else {
            int l, r, d; cin >> l >> r >> d;
            addRange(l,r,d);                        
        }
    }
    

        
    return 0;
}

