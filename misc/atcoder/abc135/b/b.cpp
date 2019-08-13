#include <bits/stdc++.h>
using namespace std;
using ll = long long;

bool isSorted(vector<int> a) {
    for (int i = 0; i < a.size() - 1; i++) {
        if (a[i] > a[i+1]) return false;
    }
    return true;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N; cin >> N;
    vector<int> a;
    for (int i = 0; i < N; i++) {
        int ai; cin >> ai;
        a.push_back(ai);
    }
    if (isSorted(a)) {
        cout << "YES\n";
        return 0;
    }
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            swap(a[i],a[j]);
            if (isSorted(a)) {
                cout << "YES\n";
                return 0;
            }
            swap(a[i],a[j]);
        }
    }
    cout << "NO\n";
}

