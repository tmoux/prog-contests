#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;



int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        int ai; cin >> ai;
        cout << (ai % 2 ? ai : ai - 1) << ' ';
    }


    return 0;
}
	

