#include <iostream>
#include <vector>
using namespace std;
typedef unsigned long long ull;

struct ResArray
{
    ull arr[100000];
    int idx = 0;
};
int msb(ull x) {
    int res = 0;
    while (x >>= 1) {
        res++;
    }
    return res;
}

int main()
{
    //input
    ull X, d; cin >> X >> d;
    ull curr = 1;
    ResArray res;
    //break up X into sums of 2^n-1
    while (X) {
        int n = msb(X+1);
        for (int i = 0; i < n; i++) {
            res.arr[res.idx++] = curr;
        }
        curr += (d+1);
        ull sub = (1 << n) - 1;
        X -= sub;
    }
    //check if answer is valid;
    if (res.idx > 10000) {
        cout << "-1\n";
        return 0;
    }
    //output answer
    cout << res.idx << '\n';
    for (int i = 0; i < res.idx; i++) {
        cout << res.arr[i] << ' ';
    }
}
