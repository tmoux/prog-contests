#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define all(x) begin(x),end(x)

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    vector<int> a = {1,3,2,6,3};
    cout << accumulate(all(a),1,[](auto a, auto b) {return a*b;}) << '\n';
}

