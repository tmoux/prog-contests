#include <bits/stdc++.h>
using namespace std;
using ll = long long;

bool isEven(ll x) {
    while (x) {
        int d = x % 10;
        if (d&1) return false;
        x /= 10;
    }
    return true;
}

int main()
{
    int t; cin >> t;
    for (int q = 1; q <= t; q++) {
        ll N; cin >> N;
        ll over = 0;
        bool isOver = false;
        ll b = 1e17;    
        while (b) {
            int d = (N/b) % 10;
            if (!isOver) {
                if (d&1) {
                    over += (d+1) * b;    
                    isOver = true;
                }
                else {
                    over += d*b;
                }
            }
            b /= 10;
        }
        while (true) {
            bool allEven = true;
            b = 1e17;
            while (b) {
                int d = (over/b) % 10;
                if (d&1) {
                    over += b;
                    allEven = false;
                    break;
                }
                b /= 10;
            }
            if (allEven) break;
        }
        assert(isEven(over));
        ll under = 0;
        bool isUnder = false;
        b = 1e17;
        while (b) {
            int d = (N/b) % 10;
            if (!isUnder) {
                if (d&1) {
                    under += (d-1) * b;
                    isUnder = true;
                }
                else {
                    under += d*b;
                }
            }
            else {
                under += 8*b;    
            }
            b /= 10;
        }
        /*
        cout << N << ": " << over << ' ' << under << '\n';
        ll oo = N;
        while (!isEven(oo)) oo++;
        ll uu = N;
        while (!isEven(uu)) uu--;
        cout << N << ": " << oo << ' ' << uu << '\n';
        */
        cout << "Case #" << q << ": " << min(over-N,N-under) << '\n';
    }

}

