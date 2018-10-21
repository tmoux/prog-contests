#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e6+6, base = 13, M = 998244353, MOD = 1000000007;

ll inverse[maxn];
int dtoi(char c) {return c-'0'+1;}
ll modexp(ll x, ll n) {
    if (n == 0) return 1;
    if (n == 1) return x%MOD;
    if (n%2==0) return modexp((x*x)%MOD,n/2);
    return (x*modexp((x*x)%MOD,n/2))%MOD;
}

struct Hash
{
    int len;
    string str;
    ll* prefix;
    Hash(const string& s) {
        len = (int)s.size();
        str = s;
        prefix = new ll[maxn];
        prefix[0] = 0LL;
        ll mult = 1;
        for (int i = 0; i < len; i++) {
            prefix[i+1] = (prefix[i] + (dtoi(s[i])*mult)%MOD)%MOD;  
            mult = (mult*base)%MOD;
        }
    }

    ll sub(int l, int r) const { //returns hash of [l,r]
        return ((prefix[r]-prefix[l-1]+MOD)*inverse[l-1])%MOD;
    }

    bool leq(int l, int r, const Hash& rhs) const {
    	if (r-l+1 != rhs.len) return (r-l+1) < rhs.len;
    	if (rhs.len == 1) return dtoi(str[l-1]) <= dtoi(rhs.str[0]);
    	int lo = 0, hi = rhs.len+1;
    	while (lo + 1 < hi) {
    		int mid = (lo+hi)/2;
    		ll s1 = sub(l,l-1+mid);
    		ll s2 = rhs.sub(1,mid);
    		if (s1 == s2) {
    			lo = mid;
    		}
    		else hi = mid;
    	}
    	if (lo == rhs.len) return true;
    	//printf("%d: %c %c\n",lo,str[l+lo-1],rhs.str[lo]);
    	return dtoi(str[l+lo-1]) <= dtoi(rhs.str[lo]);
    }

    bool geq(int l, int r, const Hash& rhs) const {
    	if (r-l+1 != rhs.len) return (r-l+1) > rhs.len;
    	if (rhs.len == 1) return dtoi(str[l-1]) >= dtoi(rhs.str[0]);
    	int lo = 0, hi = rhs.len+1;
    	while (lo + 1 < hi) {
    		int mid = (lo+hi)/2;
    		ll s1 = sub(l,l-1+mid);
    		ll s2 = rhs.sub(1,mid);
    		if (s1 == s2) {
    			lo = mid;
    		}
    		else hi = mid;
    	}
    	if (lo == rhs.len) return true;
    	//printf("%d: %c %c\n",lo,str[l+lo-1],rhs.str[lo]);
    	return dtoi(str[l+lo-1]) >= dtoi(rhs.str[lo]);
    }

    ~Hash() {delete[] prefix;}
};

void getInverse() {
	inverse[0] = 1, inverse[1] = modexp(base,MOD-2);
	for (int i = 2; i < maxn; i++) {
        inverse[i] = (inverse[i-1] * inverse[1]) % MOD;
    }
}

ll dp[maxn]; //dp[i] = # of valid partitions starting with i
ll sfxsum(int l, int r) {
	return (dp[l] - dp[r+1] + M) % M;
}
ll f(const Hash& ha, const Hash& low, const Hash& target) {
	memset(dp,0,sizeof dp);
	dp[ha.len+1] = 1;
	for (int i = ha.len; i > 0; dp[i] = (dp[i]+dp[i+1]) % M, i--) {
		if (ha.str[i-1] == '0') {
			if (low.str[0] == '0') dp[i] = sfxsum(i+1,i+1);
			continue;
		}
		int l = ha.geq(i,min(ha.len,i+low.len-1),low) ? i+low.len-1 : i+low.len;
		int r = ha.leq(i,min(ha.len,i+target.len-1),target) ? i+target.len-1 : i+target.len-2;	
		if (r < l || l > ha.len) continue;
		r = min(r,ha.len);
		dp[i] = sfxsum(l+1,r+1);
		//cout << i << ":\n";
		//cout << l << ' ' << r << ' ' << dp[i] << '\n';
	}
	/*
	for (int i = 1; i <= ha.len; i++) {
		cout << i << ": " << sfxsum(i,i) << '\n';
	}
	*/	
	return sfxsum(1,1);
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    getInverse();
    string a, l, r; cin >> a >> l >> r;
    Hash ha(a), hl(l), hr(r);
    ll ff = f(ha,hl,hr);
    cout << ff << '\n';

    return 0;
}