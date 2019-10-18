#include <bits/stdc++.h>
using namespace std;
using ll = long long;

double median(vector<int> v) {
    if (v.size() % 2 == 0) {
        return (double)(v[v.size()/2]+v[v.size()/2-1])/2.0;
    }
    else {
        return v[v.size()/2];
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    int half = n/2;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    cout << fixed << setprecision(10);
    sort(a.begin(),a.end());
    cout << a[0] << ' ' << a[n-1] << ' ';
    vector<int> firstHalf;
    for (int i = 0; i < half; i++) {
        firstHalf.push_back(a[i]);
    }
    cout << median(firstHalf) << ' ';
    cout << median(a) << ' ';
    vector<int> lastHalf;
    for (int i = n-half; i < n; i++) {
        lastHalf.push_back(a[i]);
    }
    cout << median(lastHalf) << '\n';
}

