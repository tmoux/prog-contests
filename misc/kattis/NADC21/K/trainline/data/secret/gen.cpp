#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;

void rand_data() {
    ll n = 100000;
    ll k = 99900;
    cout << n << " " << k << endl;

    unordered_set<ll> used;
    vi d(n);
    for (ll i = 0; i < n; ++i) {
        while (true) {
            d[i] = rand()%1000000;
            if (!used.count(d[i])) {
                used.insert(d[i]);
                break;
            }
        }
    }

    sort(d.begin(), d.end());
    for (ll i = 0; i < n; ++i) {
        cout << 1+rand()%100 << " " << d[i] << endl;
    }
}

void clumpy() {
    ll n = 100000;
    ll k = 10000;
    cout << n << " " << k << endl;
    ll spot = 0;
    /*for (ll i = 0; i < (n-k)/2; ++i) {
        cout << 1+rand()%100 << " " << spot++ << endl;
    }


    for (ll i = n-k; i < n; ++i) {
        cout << 99+rand()%2 << " " << spot++ << endl;
    }
    for (ll i = (n-k)/2; i < n-k; ++i) {
        cout << 97+rand()%4 << " " << spot++ << endl;
    }*/
    for (ll i = 0; i < n; ++i) {
        cout << 1 + rand()%(100*i/n+1) << " " << spot++ << endl;
    }
}

void consecutive() {
    ll n = 100000;
    ll k = 15000;
    cout << n << " " << k << endl;

    for (ll i = 0; i < n; ++i) {
        cout << 97 + rand()%4 << " " << i << endl;
    }
}

void heuristic_breaker() {
    ll n = 100000;
    ll k = 40000;
    cout << n << " " << k << endl;

    for (ll i = 0; i < k; ++i) {
        cout << 95+rand()%5 << " " << i << endl;
    }

    unordered_set<ll> used;
    vi d(n-k*2);
    for (ll i = 0; i < n-k*2; ++i) {
        while (true) {
            d[i] = 1000 + rand()%100000;
            if (!used.count(d[i])) {
                used.insert(d[i]);
                break;
            }
        }
    }

    sort(d.begin(), d.end());
    for (ll i = 0; i < n-k*2; ++i) {
        cout << 1+rand()%30 << " " << d[i] << endl;
    }

    for (ll i = 0; i < k; ++i) {
        cout << 95 + rand()%5 << " " << i+101000 << endl;
    }
}

void heuristic_breaker2() {
    ll n = 100000;
    ll k = 10000;
    cout << n << " " << k << endl;

    for (ll i = 0; i < k; ++i) {
        cout << 100 << " " << i*100 << endl;
    }

    for (ll i = 0; i < n-k*2; ++i) {
        cout << 1+rand()%20 << " " << 1000 + i*100 << endl;
    }

    for (ll i = 0; i < k; ++i) {
        cout << 100 << " " << n*100 + 1000 + i*100 << endl;
    }
}

int main() {
    clumpy();
    //heuristic_breaker();
    //consecutive();
    //heuristic_breaker();
    //rand_data();
}
