#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

const int maxn = 100;
int n;

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    string s; cin >> s;
    n = s.size();

    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'Q') {
            for (int j = i+1; j < n; j++) {
                if (s[j] == 'A') {
                    for (int k = j + 1; k < n; k++) {
                        if (s[k] == 'Q') {
                            ans++;
                        }
                    }
                }
            }
        }
    }
    cout << ans << '\n';

    return 0;
}
	

