#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <set>
using namespace std;
typedef long long ll;

bool isValid(int x) {
    int cp = x;
    set<int> digits;
    while (x) {
        digits.insert(x % 10);
        x /= 10;
    }
    
    if (digits.size() == 7 && *digits.begin() != 0) {
        for (int i: digits) {
            if (cp % i != 0) return false;
        }
        return true;
    }
    return false;
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    int x = 1000000;
    while (!isValid(x)) {
        x++;
    }
    cout << x << '\n';


    return 0;
}
	

