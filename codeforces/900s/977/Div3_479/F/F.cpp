#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <unordered_map>
using namespace std;
typedef long long ll;

const int maxn = 200005;
int arr[maxn];
int n;
int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    unordered_map<int,int> dp;
    int longestStreak = -1;
    int idx;
    for (int i = 0; i < n; i++) {
        dp[arr[i]] = dp[arr[i]-1] + 1;
        if (dp[arr[i]] > longestStreak) {
            longestStreak = dp[arr[i]];
            idx = i;
        }
    }
    //print out answer
    int curr = arr[idx] - longestStreak + 1;
    cout << longestStreak << '\n';
    for (int i = 0; i < n; i++) {
       if (arr[i] == curr) {
           cout << (i+1) << ' ';
           curr++;
       }
    }


    return 0;
}
	

