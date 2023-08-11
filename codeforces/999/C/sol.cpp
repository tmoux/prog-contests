#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

const int maxn = 400005;
int n, k;
string s;
int freq[26];
int pre[26];

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k >> s;
    for (char c: s) {
        freq[c-'a']++;
    }
    int last, rem;
    pre[0] = freq[0];
    for (int i = 1; i < 26; i++) {
        pre[i] = pre[i-1] + freq[i];
    }
    for (int i = 0; i < 26; i++) {
        if (pre[i] >= k) {
            last = i;
            if (i == 0) {
                rem = k;
            }
            else {
                rem = k - pre[i-1];
            }
            break;
        }
    }
    string ans;
    for (char c: s) {
        if (c-'a' > last) {
            ans += c;
        }
        else if (c-'a' == last) {
            if (rem == 0) {
                ans += c;
            }
            else {
                rem--;
            }
        }
    }
    
    cout << ans << '\n';

    return 0;
}
	

