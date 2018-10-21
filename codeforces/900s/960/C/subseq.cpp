#include <iostream>
#include <vector>
using namespace std;
typedef unsigned long long ull;

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
    vector<ull> nums;
    ull curr = 1;
    //break up X into sums of 2^n-1
    while (X) {
        int n = msb(X+1);
        nums.insert(nums.end(), n, curr);
        curr += (d+1);
        ull sub = (1 << n) - 1;
        X -= sub;
    }
    //check if answer is valid;
    if (nums.size() > 10000) {
        cout << "-1\n";
        return 0;
    }
    //output answer
    cout << nums.size() << '\n';
    for (ull i: nums) {
        cout << i << ' ';
    }
}
