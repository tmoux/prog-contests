#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

const int maxn = 100005;
int n, p;
vector<int> a;
int dist(char a, char b) {
    int aa = (int)(a-'a');
    int bb = (int)(b-'a');
    return min(abs(aa-bb),26-abs(aa-bb));
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> p;
    p--;
    string s; cin >> s;
    if (p >= n/2) {
        p = n - p - 1;
        reverse(s.begin(),s.end());
    }
    
    int ans = 0;
    for (int i = 0; i < s.size()/2; i++) {
        ans += dist(s[i],s[n-i-1]);
    }
    int l = -1, r = -1;
    for (int i = p-1; i >= 0; --i) {
        if (s[i] != s[n-i-1]) {
            l = i;
        }
    }
    for (int i = p+1; i < n/2; i++) {
        if (s[i] != s[n-i-1]) {
            r = i;
        }
    }
    //cout << p << ' ' << l << ' ' << r << '\n';
    if (l == -1 && r == -1) {

    }
    else if (l == -1) {
        ans += abs(r - p);
    }
    else if (r == -1) {
        ans += abs(p-l);
    }
    else {
        ans += min(abs(r-p),abs(p-l)) + abs(r-l);
    }
    cout << ans << '\n';

    return 0;
}
	

