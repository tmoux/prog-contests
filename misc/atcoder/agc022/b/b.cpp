#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N; cin >> N;
    if (N == 3) {
        cout << "2 5 63\n";
        return 0;
    }
    vector<int> ans = {2,4,3,9};
    N -= 4;
    int curr = 15;
    while (N >= 2 && curr+6 <= 30000) {
        ans.push_back(curr);
        ans.push_back(curr+6);
        curr += 12;
        N -= 2;
    }
    curr = 8;
    while (N >= 2 && curr+2 <= 30000) {
        ans.push_back(curr);
        ans.push_back(curr+2);
        curr += 6;
        N -= 2;
    }
    curr = 6;
    while (N > 0 && curr <= 30000) {
        ans.push_back(curr);
        curr += 6;
        N--;
    }
    //output
    //cout << "sz = " << ans.size() << '\n';
    for (int i: ans) {
        cout << i << ' ';
    }
    cout << '\n';
}

