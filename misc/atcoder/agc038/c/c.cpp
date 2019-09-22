#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int M = 998244353;;
const int maxn = 2e5+5;
int n, a[maxn];

vector<int> divi;

int cnt[1000006];

void getDiv(int x) {
    divi.clear();
    for (int i = 2; i*i <= x; i++) {
        if (x % i == 0) {
            divi.push_back(i);
            if (x/i != i) divi.push_back(x/i);
        }
    }
}

ll madd(ll a, ll b) {
    return (a+b) % M;
}

ll mult(ll a, ll b) {
    return (a*b) % M;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
}

