#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n;
ll ch2(ll x) {
    if (x < 2) return 0;
    return 1LL*x*(x-1)/2;
}

ll calc(ll s) {
    return ch2(s+2) - 3*ch2(s-n+2) + 3*ch2(s-2*n+2) - ch2(s-3*n);
}

ll calc2(ll i, ll s) {
    ll x = s-i;
    return max(0LL,(x+1)) - 2*max(0LL,(x+1-n)) + max(0LL,(x+1-2*n));
}

class IterateOverACube
{
    public:
    vector<int> findCell(int N, ll index) {
        n = N;
        int s = 0;
        for (; s <= 3*N-3; s++) {
            if (calc(s) > index) break;
            else index -= calc(s);
        }
        int i = 0;
        //cout << "index = " << index << endl;
        for (; i <= N-1; i++) {
            //cout << i << ": " << calc2(i,s) << endl;
            if (calc2(i,s) > index) break;
            else index -= calc2(i,s);
        }
        /*
        cout << "i = " << i << endl;
        cout << "index = " << index << endl;
        */
        int s2 = s-i;
        int j = 0;
        for (; j <= N-1; j++) {
            int k = s2-j;
            if (k >= N) continue;
            else {
                if (index == 0) {
                    return {i,j,k};
                }
                else index--;
            }
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    IterateOverACube t;
    ll n, index; cin >> n >> index;
    auto v = t.findCell(n,index);
    for (auto i: v) {
        cout << i << ' ' ;
    }
    cout << '\n';
}

