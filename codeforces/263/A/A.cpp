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
    int row, col;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            int d; cin >> d;
            if (d == 1) {
                row = i;
                col = j;
            }
        }
    }
    cout << (abs(row-2) + abs(col-2)) << '\n';


    return 0;
}
	

