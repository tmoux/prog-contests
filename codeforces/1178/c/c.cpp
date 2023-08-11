#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int M = 998244353;
int w, h;

int modexp(int a, int b) {
    int res = 1;
    while (b) {
        if (b&1) res = (1LL*res*a) % M;
        a = (1LL*a*a) % M;
        b >>= 1;
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> w >> h;
    cout << modexp(2,w+h) << '\n';


}

