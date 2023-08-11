#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

bool isVowel(char c) {
    return (c == 'a' || c == 'o' || c == 'u' || c == 'i' || c == 'e');
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    string s; cin >> s;
    bool is = true;
    for (int i = 0; i < s.size() - 1; i++) {
        if (!isVowel(s[i]) && s[i] != 'n') {
            if (!isVowel(s[i+1])) {
                cout << "NO" << '\n';
                return 0;
            }
        }
    }
    if (s[s.size()-1] == 'n' || isVowel(s[s.size()-1])) {
        cout << "YES" << '\n';
    }
    else {
        cout << "NO\n";
    }


    return 0;
}
	

