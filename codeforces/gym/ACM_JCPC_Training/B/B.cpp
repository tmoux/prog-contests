#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
int n, k;
int bucket[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    fill(bucket,bucket+maxn,2000000000);
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        int r = i/k;
        int ai; cin >> ai;
        bucket[r] = min(bucket[r],ai);     
    }
    for (int i = 0; i <= (n-1)/k; i++) {
        cout << bucket[i] << ' ';
    }

    return 0;
}

