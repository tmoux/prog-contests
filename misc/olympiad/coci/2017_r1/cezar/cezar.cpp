#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int cnt[12];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    for (int i = 2; i <= 10; i++) {
        cnt[i] = 4;
    }
    cnt[11] = 4;
    cnt[10] += 12;
    int n; cin >> n;
    int sum = 0;
    for (int i = 0; i < n; i++) {
        int ai; cin >> ai;
        cnt[ai]--;
        sum += ai;
    }

    int X = 21 - sum;
    int numLeq = 0, numGreater = 0;
    for (int i = 2; i <= 11; i++) {
        if (i <= X) numLeq += cnt[i];
        else numGreater += cnt[i];
    }

    cout << (numGreater >= numLeq ? "DOSTA" : "VUCI") << '\n';



    return 0;
}
	

