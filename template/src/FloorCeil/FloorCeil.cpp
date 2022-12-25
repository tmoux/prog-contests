// Functions to handle negative floor/ceil division
ll floor(ll a, ll b) {
  if (b < 0) return floor(-a, -b);
  if (a >= 0) return a / b;
  else return (a - b + 1) / b;
}

ll ceil(ll a, ll b){
	ll res=a/b;
	if(b*res!=a)res+=(a>0)&(b>0);
	return res;
}
