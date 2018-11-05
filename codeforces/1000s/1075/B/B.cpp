#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
const int INF = 2e9;
int n, m;
int x[2*maxn], isDriver[2*maxn];
int idOfMin[2*maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < n + m; i++) {
        cin >> x[i];
    }
    for (int i = 0; i < n + m; i++) {
        cin >> isDriver[i];
    }
    int left = -1;
    for (int i = 0; i < n + m; i++) {
        if (isDriver[i]) {
            left = i;
        }
        else {
            idOfMin[i] = left;    
        }
    }
    int right = -1;
    for (int i = n + m - 1; i >= 0; i--) {
        if (isDriver[i]) {
            right = i;
        }
        else {
            int dist = right == -1 ? INF : abs(x[i]-x[right]);
            int ldist = idOfMin[i] == -1 ? INF : abs(x[i]-x[idOfMin[i]]);
            if (dist < ldist) {
                idOfMin[i] = right;
            }
        }
    }
    vector<int> ans(n+m);
    for (int i = 0; i < n + m; i++) {
        if (!isDriver[i]) {
            ans[idOfMin[i]]++;
        }
    }
    for (int i = 0; i < n + m; i++) {
        if (isDriver[i]) {
            cout << ans[i] << ' ';
        }
    }

    return 0;
}

