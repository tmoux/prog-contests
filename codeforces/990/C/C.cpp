#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <unordered_map>
using namespace std;
typedef long long ll;

const int maxn = 300005;
int n;
pair<int,int> ps[maxn];
unordered_map<int,ll> numRights;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        int left = 0, right = 0;
        bool leftValid = true, rightValid = true;
        for (char c: s) {
            if (c == '(') {
                left++;
            }
            else {
                if (left > 0) {
                    left--;
                }
                else {
                    leftValid = false;
                }
            }
        }
        reverse(s.begin(),s.end());
        for (char c: s) {
            if (c == ')') {
                right++;
            }
            else {
                if (right > 0) {
                    right--;
                }
                else {
                    rightValid = false;
                }
            }
        }
        if (leftValid) ps[i].first = left;
        else ps[i].first = -1;
        if (rightValid) { 
            ps[i].second = right;
            numRights[ps[i].second]++;
        }
    }

    ll ans = 0;
    for (int i = 0; i < n; i++) {
        if (ps[i].first >= 0) ans += numRights[ps[i].first];
    }
    cout << ans << '\n';


    return 0;
}
	

