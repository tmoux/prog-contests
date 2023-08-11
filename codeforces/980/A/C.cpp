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
    string s; cin >> s;
    int pearls = 0, dashes = 0;
    for (char c: s) {
        switch (c) {
            case '-':
                dashes++;
                break;
            case 'o':
                pearls++;
                break;
        }
    }
    cout << ((pearls == 0 || dashes % pearls == 0) ? "YES" : "NO") << '\n';
    return 0;
}
	

