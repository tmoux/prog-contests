#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n;
ll H3(int s) {
    return s < 0 ? 0 : (s+2LL) * (s+1)/2;
}
ll f3(int s, int n) {
    return H3(s) - 3*H3(s-n) + 3*H3(s-2*n);
}
ll H2(int s) {
    return s < 0 ? 0 : s+1;
}
ll f2(int s, int n) {
    return H2(s) - 2*H2(s-n);
}

class IterateOverACube
{
    public:
    vector<int> findCell(int N, ll index) {
        n = N;
        int s = 0;
        while (index >= f3(s,N)) {
            index -= f3(s,N);
            s++;
        }
        int x = 0;
        while (x + 1 < N && index >= f2(s-x,N)) {
            index -= f2(s-x,N);
            x++;
        }
        int y = max(0,s-x-(N-1));
        return vector<int>{x,y,s-x-y};
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
