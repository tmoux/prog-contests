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
    int x = 0;
    while (n--) {
        string s; cin >> s;
        if (s == "++X" || s == "X++") {
            x++;
        }
        else x--;
    }
    cout << x << '\n';


    return 0;
}
	

