#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

string s, t;
int n;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> s >> t;
    //check if possible
    map<char,int> f1, f2;
    for (char c: s) {
        f1[c]++;
    }
    for (char c: t) {
        f2[c]++;
    }
    for (auto p: f1) {
        if (f2[p.first] != p.second) {
            //not possible
            cout << -1 << '\n';
            return 0;
        }
    }
    //now it is possible
    vector<int> ans;
    for (int i = 0; i < n; i++) {
        if (s[i] == t[i]) continue;
        int j = i + 1;
        while (s[j] != t[i]) j++;
        for (int a = j - 1; a >= i; a--) {
            swap(s[a],s[a+1]);
            ans.push_back(a+1);
        }
    }
    //output
    cout << ans.size() << '\n';
    for (int i: ans) {
        cout << i << ' ';
    }

    return 0;
}
	

