#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 3e5+5;
int n, x1, x2;
pair<int,int> a[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> x1 >> x2;
    for (int i = 0; i < n; i++) {
        cin >> a[i].first;
        a[i].second = i+1;
    }
    sort(a,a+n);
    bool swapped = false;
    for (int q = 0; q < 2; q++) {
        int idx = -1;
        for (int i = n-1; i >= 0; i--) {
            if ((double)x2/(n-i) <= a[i].first) {
                idx = i;
                break;
            }
        }
        //cout << "idx = " << idx << endl;
        for (int i = 0; i < n; i++) {
            int need = (int)ceil((double)x1/a[i].first);
            //cout << i << ": " << need << endl;
            if (i+need <= idx) {
                cout << "Yes\n";
                if (!swapped) {
                    cout << need << ' ' << (n-idx) << '\n';
                    for (int j = i; j < i+need; j++) {
                        cout << a[j].second << ' ';
                    }
                    cout << '\n';
                    for (int j = idx; j < n; j++) {
                        cout << a[j].second << ' ';
                    }
                    cout << '\n';
                }
                else {
                    cout << (n-idx) << ' ' << need << '\n';
                    for (int j = idx; j < n; j++) {
                        cout << a[j].second << ' ';
                    }
                    cout << '\n';
                    for (int j = i; j < i+need; j++) {
                        cout << a[j].second << ' ';
                    }
                    cout << '\n';
                }
                return 0;
            }
        }
        swapped = true;
        swap(x1,x2);
    }
    cout << "No\n";
}

