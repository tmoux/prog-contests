#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    string s;
    int k; 
    cin >> s >> k;
    int n = s.size();
    k = n-k;
    if (n-2*k <= 0) {
        cout << "Yes\n";
    }
    else {
        vector<char> v;
        for (int i = 0; i < k; i++) v.push_back(s[i]);
        for (int i = n-1; i > n-1-k; i--) v.push_back(s[i]);
        sort(v.begin(),v.end());
        string t = s;
        for (int i = 0; i < k; i++) {
            t[i] = v[i];
        }
        for (int i = n-1; i > n-1-k; i--) {
            t[i] = v.back();
            v.pop_back();
        }
        string sorted = s;
        sort(sorted.begin(),sorted.end());
        //cout << t << endl;
        cout << (t == sorted ? "Yes": "No") << endl;
    }
}

