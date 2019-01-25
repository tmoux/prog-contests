#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve() {
    int n; cin >> n;
    int curr = 1;
    stack<int> st;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = n-1; i >= 0; i--) {
        if (curr == a[i]) {
            curr++;    
        }
        else {
            while (!st.empty() && st.top() == curr) {
                curr++;
                st.pop();
            }
            st.push(a[i]);    
        }
    }
    while (!st.empty() && st.top() == curr) {
        curr++;
        st.pop();
    }
    //cout << curr << '\n';
    cout << (curr == n+1 ? "Y" : "N") << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}

