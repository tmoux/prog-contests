#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, k;

set<int> on;

int main() {
    cin >> n >> k;
    deque<int> deq;
    for (int i = 0; i < n; i++) {
        int id; cin >> id;
        if (on.count(id)) {
            continue;
        }
        else {
            if (deq.size() == k) {
                on.erase(deq.back());
                deq.pop_back();
            }
            deq.push_front(id);
            on.insert(id);
        }
    }
    cout << deq.size() << '\n';
    for (int i: deq) {
        cout << i << ' ';
    }
    cout << '\n';
}

