#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

bool isLeap(int y) {
    if ((y % 400 == 0) || (y % 4 == 0 && y % 100 != 0)) {
        return true;
    }
    return false;
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    int y; cin >> y;
    int mode = 0;
    bool leap = isLeap(y);
    int x = y;
    int newmd = mode;
    while (x == y || mode != newmd || leap != isLeap(x)) {
        x++;
        newmd = (newmd + 1) % 7;
        if (isLeap(x)) {
            newmd = (newmd + 1) % 7;
        }
    }
    cout << x << '\n';



    return 0;
}
	

