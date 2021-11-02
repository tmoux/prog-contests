//each is x mod p_i = a_i
ll p[maxn], a[maxn];
//for quickmult see pollard rho
ll exgcd(ll x, ll y,ll & a, ll & b){
    if (y == 0){
        a = 1;b = 0;return x;
    }
    ll d = exgcd(y, x%y, a, b);
    ll temp = a; a = b; b = temp - (x / y) * b;
    return d;
}

int first_nontrivial = 0;
ll current_p ;
ll sol = 0; //this is the solution
for (int i = 1;i <= n;i++){
  if (p[i] != 1){
    first_nontrivial = i;
    current_p = p[i]; sol = a[i];
    break;
  }
}
for (int i = first_nontrivial+1;i <= n;i++){
  ll x,y;
  if (p[i] == 1) continue;
  ll d = exgcd(current_p, p[i], x, y);
  ll r = ((a[i] - sol) % p[i] + p[i])%p[i];
  ll temp = quickmult(x, r / d,p[i] / d);
  sol = sol + current_p * temp;
  current_p = current_p / d * p[i];
  sol = (sol % current_p + current_p) % current_p;
}
