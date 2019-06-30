#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e6+6, M = 1e9+7;
int N, K;

void madd(int& a, int b) {
    a = (a+b)%M;
}
void msub(int& a, int b) {
    a = (a-b+M)%M;
}
int mult(int a, int b) {
    return (1LL*a*b)%M;
}

int modexp(int a, int b) {
    int res = 1;
    while (b) {
        if (b&1) res = mult(res,a);
        a = mult(a,a);
        b >>= 1;
    }
    return res;
}

struct Bag
{
    multiset<int> s;
    int delta = 0;
    void insert(int x) {
        s.insert(x-delta);            
    }
    void addAll(int x) {
        delta += x;
    }
    int extractMin() {
        return *s.begin() + delta;
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    for (int qq = 1; qq <= t; qq++) {
        cin >> N >> K;
        vector<int> vec;
        int ans = 0;
        for (int i = 1; i <= N; i++) {
            char c; cin >> c;
            vec.push_back(c);
            if (c == 'B') madd(ans,modexp(2,i));
        }
        Bag b;
        b.insert(0);
        //assume they all start as A's
        for (int i = N; i >= 1; i--) {
            char c = vec.back(); vec.pop_back();
            if (c == 'A') {
                b.insert(0);
                b.addAll(1);
            }
            else {
                int mn = min(b.extractMin()-1,-1);
                if (mn >= -K) {
                    //ok to make it a B
                    b.insert(0);
                    b.addAll(-1);
                    msub(ans,modexp(2,i));
                }
                else {
                    //keep it as an A
                    b.insert(0);
                    b.addAll(1);
                }
            }
        }
        cout << "Case #" << qq << ": " << ans << endl;
    }
}

