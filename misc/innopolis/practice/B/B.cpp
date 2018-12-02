#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    int n; scanf("%d\n",&n);
    int r = 0;
    while (n--) {
        string s; getline(cin,s);
        int dots = -1;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '.') {
                if (dots != -1) {
                    dots = -2;
                }
                else {
                    dots = i;
                }
            }
        }
        if (dots < 0) continue;
        if (1 <= dots && dots <= 8 && 1 <= s.size()-dots-1 && s.size() - dots - 1 <= 3) {
            //cout << s << ' ' << dots << '\n';
            r++;
        }
    }
    cout << r << '\n';

    return 0;
}

