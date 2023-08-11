#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 2e5+5;
int n;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    stack<bool> st;
    for (int i = 0; i < n; i++) {
        int ai; cin >> ai;
        if (st.empty()) {
            st.push(ai&1);
        }
        else {
            bool t = st.top();
            if (!(t^(ai&1))) {
                st.pop();
            }
            else {
                st.push(ai&1);    
            }
        }
    }
    cout << (st.size() <= 1 ? "YES" : "NO") << '\n';

    return 0;
}

