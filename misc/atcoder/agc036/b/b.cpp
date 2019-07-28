#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int a[maxn];
int n;
ll k;
bool has[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    memset(has,false,sizeof has);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<int> curr;
    for (int qq = 0; qq < k; qq++) {
        for (int i = 0; i < n; i++) {
            if (find(curr.begin(),curr.end(),a[i]) != curr.end()) {
                while (curr.back() != a[i]) {
                    curr.pop_back();
                }
                curr.pop_back();
            }
            else {
                curr.push_back(a[i]);
            }
        }
        for (int i: curr) {
            cout << i << ' ';
        }
        cout << '\n';
    }
    /*
    for (int i: curr) {
        cout << i << ' ';
    }
    cout << '\n';
    */
}

