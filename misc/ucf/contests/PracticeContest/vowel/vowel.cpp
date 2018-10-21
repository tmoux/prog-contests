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
    string vowels = "aeiou";
    int ans = 0;
    for (char c: s) {
        if (find(vowels.begin(),vowels.end(),c) != vowels.end()) {
            ans++;
        }
    }

    cout << (ans * 2 > s.size() ? 1 : 0) << '\n';


    return 0;
}
	

