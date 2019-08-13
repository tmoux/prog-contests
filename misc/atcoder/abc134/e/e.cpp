#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N; cin >> N;
    multiset<int> ms;
    for (int i = 0; i < N; i++) {
        int ai; cin >> ai;
        auto it = ms.lower_bound(ai);
        if (it == ms.begin()) {
            ms.insert(ai);
        }
        else {
            --it;
            ms.erase(it);
            ms.insert(ai);
        }
    }
    cout << ms.size() << '\n';
}

