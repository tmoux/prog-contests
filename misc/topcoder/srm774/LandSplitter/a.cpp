#include <bits/stdc++.h>
using namespace std;
using ll = long long;

class LandSplitter
{
    public:
    ll cheapest(int N, int A, int B) {
        if (N < A) return -1;
        if (A == B) {
            return N % A == 0 ? (1LL*N*N-(N/A)*A*A)/2 : -1;
        }
        ll ans = 1e18;
        for (int i = 1; ; i++) {
            if (1LL*i*B < N) continue;
            int n = N-1LL*i*A;
            if (n < 0) break;
            int numBig = n/(B-A);
            int small = n % (B-A);
            ll tr = 1LL*numBig*B*B + 1LL*(small+A)*(small+A);
            int left = i-numBig-1;
            tr += 1LL*left*A*A;
            /*
            cout << i << ": " << tr << '\n';
            cout << numBig << ' ' << small << '\n';
            */
            ans = min(ans,(1LL*N*N-tr)/2);
        }
        return ans == 1e18 ? -1 : ans;
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    LandSplitter t;
    int n, a, b; cin >> n >> a >> b;
    cout << t.cheapest(n,a,b) << '\n';
}

