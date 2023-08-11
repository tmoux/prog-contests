#include <iostream>
#include <stack>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
int n, A[maxn], T[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    stack<int> st;
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }

    int maxans = 0;
    for (int i = 0; i < n; i++) {
        while (!st.empty() && A[st.top()] < A[i]) {
            T[i] = max(T[i],T[st.top()] + 1);
            st.pop();
        }
        if (st.empty()) T[i] = -1;
        st.push(i);
        maxans = max(maxans,T[i]+1);
    }

    cout << maxans << '\n';

    return 0;
}
	

