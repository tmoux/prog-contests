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
    string s; cin >> s;
    int numOnes = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '1') numOnes++;
    }

    //output
    if (numOnes > 0) cout << '1';
    for (int i = 0; i < n-numOnes; i++) {
        cout << '0';
    }
    cout << '\n';


    return 0;
}
	

