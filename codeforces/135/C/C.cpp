#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

int a, b, c;

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    string s; cin >> s;
    for (char c: s) {
        if (c == '1') a++;
        else if (c == '0') b++;
        else c++;
    }
    //check if 00 is possible
    if (a < b + c) {
        cout << "00\n";
    }
    //check is 01 is possible
    if (


    return 0;
}
	

