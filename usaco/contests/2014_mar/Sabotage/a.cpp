#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
int N, a[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    freopen("sabotage.in","r",stdin); freopen("sabotage.out","w",stdout);
    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> a[i];
        a[i] += a[i-1];
    }
    double minans = 1e30;
    for (int i = 2; i <= N-1; i++) {
        for (int j = 2; j <= i; j++) {
            double avg = (a[N] - (a[i]-a[j-1]))/(double)(N-(i-j+1));
            minans = min(minans,avg);
            //cout << j << ' ' << i << ": " << avg << '\n';
        }
    }
    cout << fixed << setprecision(3) << minans << '\n';


    return 0;
}

