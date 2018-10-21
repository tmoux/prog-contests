#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

int N;

bool isPrime(int n) {
    for (int i = 2; i*i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

vector<int> getPrimes(int N) {
    vector<int> ret;
    int tr = 11;
    while (ret.size() != N) {
       if (isPrime(tr)) ret.push_back(tr);
       tr += 10;
    }
    return ret;
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    vector<int> primes = getPrimes(N);
    for (int i: primes) {
        cout << i << ' ';
    }



    return 0;
}
	

