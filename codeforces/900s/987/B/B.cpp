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
    int x, y; cin >> x >> y;
    if (x == y) {
        cout << "=\n";
    }
    else if (x == 1) {
        cout << "<\n";
    }
    else if (y == 1) {
        cout << ">\n";
    }
    else if (x == 2 && y == 3) {
        cout << "<\n";
    }
    else if (x == 3 && y == 2) {
        cout << ">\n";
    }
    else if ((x == 2 && y == 4) || (x == 4 && y == 2)) {
        cout << "=\n";
    }
    else {
        if (x < y) {
            cout << ">\n";
        }
        else {
            cout << "<\n";
        }
    }


    return 0;
}
	

