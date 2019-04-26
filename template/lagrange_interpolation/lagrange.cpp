using poly = vector<int>;

const int M = 1e6+3;
ll modexp(ll x, ll n) {
    if (n == 0) return 1;
    if (n == 1) return x%M;
    if (n%2==0) return modexp((x*x)%M,n/2);
    return (x*modexp((x*x)%M,n/2))%M;
}

//assume M is prime
ll modInverse(ll x) {
	return modexp(x,M-2);
}

void madd(int& a, int b) {
    a = (a + b) % M;
}

int mult(int a, int b) {
    return (1LL*a*b) % M;
}

int pos(int x) {
    while (x < 0) x += M;
    return x;
}

int eval(const poly& p, int x) { //evaluates p(x) at x
    int res = 0;
    int mul = 1;
    for (int i = 0; i < p.size(); i++) {
        madd(res,mult(mul,p[i]));
        mul = mult(mul,x);
    }
    return res;
}

poly operator*(const poly& a, const poly& b) {
    poly ans = vector<int>(a.size()+b.size()-1);
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < b.size(); j++) {
            madd(ans[i+j],mult(a[i],b[j]));
        }
    }
    return ans;
}

poly operator+(poly& a, poly& b) {
    if (a.size() < b.size()) swap(a,b);
    poly ans = a;
    for (int i = 0; i < b.size(); i++) {
        madd(ans[i],b[i]);
    }
    return ans;
}

poly scale(const poly& a, int s) {
    poly ans = a;
    for (int& i: ans) {
        i = mult(i,s);
    }
    return ans;
}

poly interpolate(vector<pair<int,int>> qs) {
    poly f;
    for (auto p: qs) {
        int x = p.first;
        int y = p.second;
        poly r = {1};
        for (auto q: qs) {
            if (p == q) continue;
            poly m = {pos(-q.first),1};
            //cout << r << ": " << m << '\n';
            r = r * m;    
            //cout << r << '\n';
        }
        for (auto q: qs) {
            if (p == q) continue;
            r = scale(r,modInverse(pos(x-q.first)));
        }
        r = scale(r,y);
        f = f + r;
    }
    return f;
}

ostream& operator<<(ostream& os, const poly& p) {
    for (int i = 0; i < p.size(); i++) {
        if (i == 0) os << p[i];
        else os << p[i] << "x^" << i;
        if (i < p.size()-1) os << " + ";
    }
    return os;
}