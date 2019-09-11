#include <bits/stdc++.h>
using namespace std;
using ll = long long;

class FixedPointReversals
{
public:
    vector<int> sort(vector<int> A, int fixed) {
        vector<int> B = A;
        sort(B.begin(),B.end());
        if (B[fixed] != A[fixed]) return -1;
        int n = A.size();
        int l = 0, r = n-1;
        while (true) {
            if (fixed - l >= r - fixed) {
                //do l

            }
            else {

            }
        }
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);


}

