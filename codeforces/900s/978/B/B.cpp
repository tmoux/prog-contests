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
    int n; string s;
    cin >> n >> s;
    int currStreak = 0;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'x') currStreak++;
        else {
            if (currStreak >= 3) {
                ans += currStreak-2;
            }
            currStreak = 0;
        }
    }
    if (currStreak >= 3) {
        ans += currStreak -2;
    }
    cout << ans << '\n';
    


    return 0;
}
	

