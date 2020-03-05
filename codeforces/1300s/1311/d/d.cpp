#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int a, b, c; cin >> a >> b >> c;
        int ans = 1e9;
        array<int,3> best = {-1,-1,-1};
        for (int A = 1; A <= 50000; A++) {
            for (int B = A; B <= 50000; B += A) {
                int C;
                if (c <= B) C = B;
                else {
                    if (c%B <= B-(c%B)) {
                        C = (c/B)*B;
                    }
                    else {
                        C = (c/B)*B + B;
                    }
                }
                int tr = abs(A-a)+abs(B-b)+abs(C-c);
                assert(A <= B && B <= C);
                if (ans > tr) {
                    ans = tr;
                    best = {A,B,C};
                }
            }
        }
        cout << ans << endl;
        cout << best[0] << ' ' << best[1] << ' ' << best[2] << endl;
    }
}

