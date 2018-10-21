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
    int num1 = 0;
    for (char c: s) num1 += c == '1';
    int num0 = 0;
    int start = -1;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '2') {
            start = i;
            break;
        }
        num0 += s[i] == '0';
    }
    for (int i = 0; i < num0; i++) {
        cout << 0;
    }
    for (int i = 0; i < num1; i++) {
        cout << 1;
    }
    if (start != -1) {
        for (int i = start; i < s.size(); i++) {
            if (s[i] != '1') cout << s[i];
        }
    }

    return 0;
}
	

