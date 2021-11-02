#include <map>
#include <ctime>
#include <cstdlib>
#include <iostream>

using namespace std;

typedef long long ll;

//Quick Multiplication - Calculate x * y mod modi efficiently
//where x and y is in long long range
ll quickmult(ll x, ll y, ll p){
    ll temp = x * y - ((ll)((long double)x / p * y + 0.5)) * p;
    return (temp < 0) ? temp + p : temp;
}

//Prime Test via Miller-Rabin

bool prime_test(ll p){
    static int tests[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    int r = 0;
    ll b = p - 1;
    if (p == 2) return true;
    if (p == 1 || (p & 1) == 0) return false;

    while ((b & 1) == 0){
        r++;
        b >>= 1;
    }
    ll d = (p - 1) / (1ll << r);
    for (int i = 0;i < 12;i++){
        if (p == tests[i]){
            return true;
        }
        ll x = quickpow2(tests[i], d, p);
        for (int j = 1;j <= r;j++){
            ll y = quickmult(x, x, p);
            if (y == 1 && x != 1 && x != p - 1) return false;
            x = y;
        }
        if (x != 1) return false;
    }
    return true;
}

//We will store factors in a global variable to save time
map<ll, int> factors;

ll abs(ll x){
    return (x < 0)? (-x) : x;
}

ll gcd(ll x, ll y){
    if (y == 0) return x;
    return gcd(y, x % y);
}

ll get_next(ll x, ll addi,ll modi){
    return (quickmult(x, x, modi) + addi);
}

//find a prime factor of n based on the seed, if we cannot find it return -1
ll rho_find(ll n, ll seed, ll addi){
    ll a = seed;
    ll b = get_next(seed, addi, n);
    while (a != b){
        ll p = gcd(abs(a - b), n);
        if (p > 1){
            if (p == n) return -1;
            return p;
        }
        a = get_next(a, addi, n);
        b = get_next(get_next(b, addi, n), addi, n);
    }
    return -1;
}

//factorizing n via pollard rho
void pollard_rho(ll n){
    if (n == 1){
        return;
    }
    if (prime_test(n)){
        factors[n]++;
        return;
    }
    ll p = -1;
    while (p == -1){
        ll addi = rand() % (n - 1) + 1;
        p = rho_find(n, rand() % (n - 1) + 1, addi);
        if (p != -1){
            pollard_rho(p);
            pollard_rho(n / p);
            return;
        }
    }
}

int main(int argc, const char * argv[]) {
    srand(0);
    int t;
    cin >> t;
    while (t--){
        ll n;
        cin >> n;
        if (prime_test(n)){
            cout << "Prime\n";
        }
        else{
            factors.clear();
            pollard_rho(n);
            cout << factors.begin()->first << endl;
        }
    }
    return 0;
}
