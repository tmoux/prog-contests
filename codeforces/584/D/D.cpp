#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

bool isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i*i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    vector<int> vec;
    int p1 = n;
    while (!isPrime(p1)) {
        p1--;
    }
    vec.push_back(p1);
    if (n - p1) {
        n -= p1;
        if (isPrime(n)) {
            vec.push_back(n);
        }
        else {
            for (int i = 2; i < n; i++) {
                if (isPrime(i) && isPrime(n-i)) {
                    vec.push_back(i);
                    vec.push_back(n-i);
                    break;
                }
            }
        }
    }
    //output
    cout << vec.size() << '\n';
    for (int i: vec) cout << i << ' ';



    return 0;
}
	

