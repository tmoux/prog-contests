#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 50005;
int N, a[2*maxn];

int bit[2*maxn];
void add(int i, int x) {
    for (; i <= 2*N; i += i & (-i))
        bit[i] += x;
}

int sum(int i) {
    int r = 0;
    for (; i; i -= i & (-i)) {
        r += bit[i];
    }
    return r;
}

int start[maxn];
bool seen[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    freopen("circlecross.in","r",stdin); freopen("circlecross.out","w",stdout);
    cin >> N;
    for (int i = 1; i <= 2*N; i++) cin >> a[i];
    int ans = 0;
    for (int i = 1; i <= 2*N; i++) {
        if (!seen[a[i]]) {
            //start
            start[a[i]] = i;
            add(i,1);
            seen[a[i]] = true;
        }
        else {
            //end, add them up
            int r = sum(i)-sum(start[a[i]]);
            //cout << i << ' ' << a[i] << ": " << r << '\n';
            ans += r;
            add(start[a[i]],-1);
        }
    }
    cout << ans << '\n';


    return 0;
}

