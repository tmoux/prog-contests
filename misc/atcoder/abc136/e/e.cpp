#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int N, A[maxn], K;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> K;
    int sum = 0;
    for (int i = 0; i < N; i++) {
        cin >> A[i];
        sum += A[i];
    }
    vector<int> facs;
    for (int i = 1; i*i <= sum; i++) {
        if (sum % i == 0) {
            facs.push_back(i);
            facs.push_back(sum/i);
        }
    }
    sort(facs.begin(),facs.end(),greater<int>());
    for (int f: facs) {
        multiset<int> mods;
        int sub = 0, add = 0;
        for (int i = 0; i < N; i++) {
            mods.insert(A[i] % f);
            add += (f - (A[i] % f));
        }
        for (int i: mods) {
            sub += i;
            add -= (f - i);
            if (sub == add && sub <= K) {
                cout << f << '\n';
                return 0;
            }
        }
    }
}

