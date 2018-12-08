#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n, k; cin >> n >> k;
        string s; cin >> s;
        vector<int> ones, zeros;
        //cout << s.size() << '\n';
        for (int i = 0; i < n; i++) {
            if (s[i] == '1') ones.push_back(i);
            else zeros.push_back(i);
        }
        reverse(ones.begin(),ones.end());
        reverse(zeros.begin(),zeros.end());
        for (int i = 0; i < n - k; i++) {
            if (i % 2 == 0) {
                //remove turn
                if (!ones.empty()) ones.pop_back();                    
                else zeros.pop_back();
            }
            else {
                if (!zeros.empty()) zeros.pop_back();
                else ones.pop_back();
            }
        }
        /*
        for (int i: ones) {
            cout << i << ' ';
        }
        cout << '\n';
        for (int i: zeros) {
            cout << i << ' ';
        }
        cout << '\n';
        */
        vector<bool> use(n,false);
        for (int i: ones) use[i] = true;
        for (int i: zeros) use[i] = true;
        for (int i = 0; i < n; i++) {
            if (use[i]) cout << s[i];
        }
        cout << '\n';
    }

    return 0;
}

