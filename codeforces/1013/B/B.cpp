#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
int n, x, A[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> x;
    map<int,int> orig, news;
    for (int i = 0; i < n; i++) {
        cin >> A[i];
        orig[A[i]]++;
        news[A[i] & x]++;
    }

    for (int i = 0; i < n; i++) {
        if (orig[A[i]] > 1) {
            //already possible
            cout << 0 << '\n';
            return 0;
        }
    }

    for (int i = 0; i < n; i++) {
        if ((A[i] != (A[i] & x) && orig[A[i] & x] >= 1) || (A[i] == (A[i] & x) && orig[A[i]&x] > 1)) {
            cout << 1 << '\n';
            return 0;
        }
    }

    for (int i = 0; i < n; i++) {
        if (news[A[i] & x] > 1) {
            cout << 2 << '\n';
            return 0;
        }
    }

    cout << -1 << '\n';


    return 0;
}
	

