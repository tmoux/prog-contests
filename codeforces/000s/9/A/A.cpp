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
    int y, w; cin >> y >> w;
    int nom = 0;
    for (int i = 1; i <= 6; i++) {
        if (i >= max(y,w)) nom++;
    }
    switch (nom) {
        case 0: cout << "0/1\n"; break;
        case 1: cout << "1/6\n"; break;
        case 2: cout << "1/3\n"; break;
        case 3: cout << "1/2\n"; break;
        case 4: cout << "2/3\n"; break;
        case 5: cout << "5/6\n"; break;
        case 6: cout << "1/1\n"; break;
    }


    return 0;
}
	

