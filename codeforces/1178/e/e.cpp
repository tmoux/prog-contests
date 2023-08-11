#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e6+6;
int n;
string s;

deque<char> f(int mid) {
    int l = mid-1;
    int r = mid+1;
    deque<char> ans;
    ans.push_back(s[mid]);
    while (l >= 0 && r < n) {
        if (s[l] == s[r]) {
            ans.push_back(s[l]);
            ans.push_front(s[r]);
        }
        else {
            if (r+1 < n && s[l] == s[r+1]) {
                ans.push_front(s[l]);
                ans.push_back(s[r+1]);
                r++;
            }
            else if (l-1 >= 0 && s[l-1] == s[r]) {
                ans.push_front(s[l-1]);
                ans.push_back(s[r]);
                l--;
            }
            else {
                if (l-1 >= 0 && r+1 < n) {
                    assert(s[l-1] == s[r+1]);
                    ans.push_front(s[l-1]);
                    ans.push_back(s[r+1]);
                    l--;
                    r++;
                }
            }
        }
        l--;
        r++;
    }
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> s;
    n = s.size();
    
    deque<char> ans = f(n/2);
    if (ans.size() < n/2 && n % 2 == 0) {
        ans = f(n/2-1);
    }
    //output
    assert(ans.size() >= n/2);
    for (char c: ans) {
        cout << c;
    }
    cout << '\n';
}

