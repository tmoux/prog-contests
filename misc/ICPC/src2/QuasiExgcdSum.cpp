/*
Using Quasi_Exgcd to sum
f(a,b,c,n) = sum_{i=0}^n \floor{(ai+b)/c}
g(a,b,c,n) = sum_{i=0}^n \floor i{(ai+b)/c}
h(a,b,c,n) = sum_{i=0}^n (\floor{(ai+b)/c})^2
all are done under mod p
*/

struct rec{
		ll f, g, h;
};

//add, sub, quickpow omitted
ll inv2 = quickpow(2, modi-2);
ll inv6 = quickpow(6, modi - 2);

rec solve(ll a, ll b, ll c, ll n){
  rec ans;
	if (a == 0){
	  ans.f = (b / c) * (n + 1) % modi;
		ans.g = (b / c) * (n + 1) % modi * n % modi * inv2 % modi;
		ans.h = (b / c) * (b / c) % modi * (n+1) % modi;
		return ans;
	}
	ans.f = ans.g = ans.h = 0;
	if (a >= c || b >= c){
	  rec temp = solve(a % c, b % c, c, n);
		add(ans.f, (a/c)*n%modi*(n+1)%modi*inv2%modi);
		add(ans.f, (b/c)*(n+1)%modi);
		add(ans.f, temp.f);
		add(ans.g, (a/c)*n%modi*(n+1)%modi*
		((2*n+1)%modi)%modi*inv6%modi);
    add(ans.g, (b/c)*n%modi*(n+1)%modi*inv2 % modi);
    add(ans.g, temp.g);
    add(ans.h, (a/c)*(a/c)%modi*n%modi*
		(n+1)%modi*((2*n+1)%modi)%modi*inv6% modi);
    add(ans.h, (b/c)*(b/c)%modi*(n+1)%modi);
    add(ans.h, (a/c)*(b/c)%modi*n%modi*(n+1)%modi);
    add(ans.h, temp.h);
    add(ans.h, 2LL * (a/c)%modi*temp.g%modi);
    add(ans.h, 2LL * (b/c)%modi*temp.f%modi);
		return ans;
	}
	if (a < c && b < c){
		ll m = (a * n + b) / c;
    rec temp = solve(c, c - b - 1, a, m - 1);
    ans.f = n * m % modi;
    sub(ans.f, temp.f);
    ans.g = n * (n + 1) % modi * m % modi;
    sub(ans.g, temp.f);
    sub(ans.g, temp.h);
    ans.g = ans.g * inv2 % modi;
    ans.h = n * m % modi * (m + 1) % modi;
    sub(ans.h, 2LL * temp.g % modi);
    sub(ans.h, 2LL * temp.f % modi);
    sub(ans.h, ans.f);
		return ans;
	}
	return ans;
}
