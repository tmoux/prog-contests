#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
int N, K, a[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> K;
    vector<int> spaces;
    spaces.reserve(N-1);
    for (int i = 0; i < N; i++) {
        cin >> a[i];
        if (i > 0) spaces.push_back(a[i]-a[i-1]-1);
    }
    sort(spaces.begin(),spaces.end(),greater<int>());
    int tot = a[N-1] + 1 - a[0];
    for (int i = 0; i < K - 1; i++) {
        tot -= spaces[i];
    }
    cout << tot << '\n';


    return 0;
}

