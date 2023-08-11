#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    string a, b; cin >> a >> b;
    if (a.size() != b.size()) {
        cout << "NO" << '\n';
        return 0;
    }
    if (a == b) {
        cout << "YES" << '\n';
        return 0;
    }

    bool b1 = false, b2 = false;
    for (char c: a) {
        b1 |= c == '1';
    }
    for (char c: b) {
        b2 |= c == '1';
    }

    cout << (b1 && b2 ? "YES" : "NO") << '\n';


    return 0;
}
	

