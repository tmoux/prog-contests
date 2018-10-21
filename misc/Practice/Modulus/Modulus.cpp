#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

template <typename integ,integ MOD>
struct Modulus
{
    integ val = 0;
    Modulus(integ v) {
        val = v;
    }
};

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    Modulus<int,1000000007> A(5);
    cout << A.val << '\n';


    return 0;
}
	

