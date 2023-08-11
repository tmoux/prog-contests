#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

int n, p;
const int maxn = 1005;
string s;

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> p >> s;
    if (p == 1) {
        cout << "NO\n";
        return 0;
    }
    else if (p == 2) {
        if (n == 1) {
            cout << (s == "a" ? "b" : "NO") << '\n';
            return 0;
        }
        cout << (s == "ab" ? "ba" : "NO") << '\n';
        return 0;
    }
    else {
        for (int i = n - 1; i >= 0; i--) {
            s[i]++;
            while ((i >= 1 && s[i] == s[i-1]) || (i >= 2 && s[i] == s[i-2])) {
                s[i]++;
            }
            if (s[i] - 'a' < p) {
                for (int j = i + 1; j < n; j++) {
                    s[j] = 'a';
                    while (s[j] == s[j-1] || (j >= 2 && s[j-2] == s[j])) {
                        s[j]++;
                    }
                }
                cout << s << '\n';
                return 0;
            }
        }
    }
    cout << "NO\n";

    return 0;
}
	

