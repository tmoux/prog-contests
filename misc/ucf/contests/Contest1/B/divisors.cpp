#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <map>
using namespace std;
typedef long long ll;

int L; ll K;
map<int,int> factors;
vector<int> vec;

void factor(int a) {
    if (a == 1) return;
    for (int i = 2; i*i <= a; i++) {
        if (a % i == 0) {
            while (a % i == 0) {
                factors[i]++;
                a /= i;
            }
            factor(a);
            return;
        }
    }
    //must be prime
    factors[a]++;
}

map<ll,int> dp[100];

int f(int i, ll k) {
    if (dp[i].find(k) != dp[i].end()) return dp[i][k];
    if (k == 1) return dp[i][k] = 1;
    if (i == vec.size() && k != 1) return dp[i][k] = 0;
    dp[i][k] = f(i+1,k);
    for (int j = 2; j <= vec[i]; j++) {
        if (k % j == 0) {
            dp[i][k] += f(i+1,k/j);
        }
    }
    return dp[i][k];
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> L >> K;
    for (int i = 0; i < L; i++) {
        int a; cin >> a;
        factor(a);
    }

    for (auto p: factors) {
        vec.push_back(p.second+1);
    }
    sort(vec.begin(),vec.end());
    int ans = f(0,K); 
    cout << ans << '\n';
    //for (int i: vec) cout << i << ' ';


    return 0;
}
	

