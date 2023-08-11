#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    string s; cin >> s;
    string hello = "hello";
    int curr = 0;
    for (char c: s) {
        if (c == hello[curr]) {
            curr++;
        }
        if (curr == 5) {
            cout << "YES" << '\n';
            return 0;
        }
    }
    cout << "NO\n";

    return 0;
}
	

