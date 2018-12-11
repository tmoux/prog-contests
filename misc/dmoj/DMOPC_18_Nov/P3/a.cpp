#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e6+5;
int N;
char arr[maxn];
int len[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> arr[i];
        //cout << arr[i] << ' ';
    }
    for (int i = 1; i <= N; i++) {
        if (i == 0 || arr[i] != arr[i-1]) len[i] = 1;
        else len[i] = len[i-1] + 1;
    }
    for (int i = N; i >= 1; i--) {
        if (arr[i] == arr[i+1]) len[i] = max(len[i],len[i+1]);    
        //cout << i << ": " << len[i] << '\n';
    }
    ll ans = 0;
    for (int i = 1; i <= N; i++) {
        ll add = min(len[i],min(i,N-i+1));
        ans += add;
    }
    for (int i = 1; i <= N - 1; i++) {
        ll add;
        if (arr[i] == arr[i+1]) {
            add = min(len[i],min(i,N-i));
        }
        else {
            add = min(max(len[i],len[i+1]),min(i,N-i));    
        }
        ans += add;
    }
    cout << ans << '\n';

    return 0;
}

