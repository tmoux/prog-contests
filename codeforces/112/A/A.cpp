#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

string s1, s2;

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> s1 >> s2;
    for (int i = 0; i < s1.size(); i++) {
        s1[i] = tolower(s1[i]);
        s2[i] = tolower(s2[i]);
    }
    if (s1 < s2) {
        cout << "-1\n";
    }
    else if (s2 < s1) {
        cout << "1\n";
    }
    else {
        cout << "0\n";
    }

    return 0;
}
	

