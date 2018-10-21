#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <set>
using namespace std;
typedef long long ll;

const int maxn = 200005;
int n;
ll A[maxn];
set<ll> s;

bool isTwo(int n) {
    return (n == 0 ? false : (n & (n-1)) == 0);
}

int dist(int a, int b) {
    return abs(a-b);
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> A[i];
        s.insert(A[i]);
    }
    sort(A,A+n);
    //look for 3
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < 32; k++) {
            if (s.find(A[i] + (1 << k)) != s.end() && s.find(A[i] + (1 << (k+1))) != s.end()) {
                cout << 3 << '\n';
                cout << A[i] << ' ' << (A[i] + (1 << k)) << ' ' << (A[i] + (1 << (k+1))) << '\n';
                return 0;
            }
        }
    }

 for (int i = 0; i < n; i++) {
        for (int k = 0; k < 32; k++) {
            if (s.find(A[i] + (1 << k)) != s.end()) {
                cout << 2 << '\n';
                cout << A[i] << ' ' << (A[i] + (1 << k)) << '\n';
                return 0;
            }
        }
    }
    
    cout << "1\n";
    cout << A[0] << '\n';


    return 0;
}
	

