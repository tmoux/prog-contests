#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n;
string curr;
vector<string> ans;
void recurse(int i, char c) {
    if (i == n) {
        ans.push_back(curr);
        return;
    }
    for (char b = 'a'; b <= c+1; b++) {
        curr += b;
        recurse(i+1,b==c+1?c+1:c);
        curr.pop_back();
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    recurse(0,'a'-1); 
    sort(ans.begin(),ans.end());
    for (auto s: ans) {
        cout << s << '\n';
    }
}
