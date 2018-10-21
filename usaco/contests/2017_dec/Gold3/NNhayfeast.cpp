#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
int N, F[maxn], S[maxn];
ll M;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    freopen("hayfeast.in","r",stdin);
    freopen("hayfeast.out","w",stdout);
    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        cin >> F[i] >> S[i];
    }
    multiset<int> spicy;
    int ans = 2e9+9;
    ll sum = 0;
    int R = 1;
    for (int i = 1; i <= N; i++) {
        sum -= F[i-1];
        auto it = spicy.find(S[i-1]);
        if (it != spicy.end()) spicy.erase(it);
        while (R <= N && sum < M) {
            sum += F[R];
            spicy.insert(S[R]);
            R++;
        }
        if (sum < M && R > N) break;
        ans = min(ans,*spicy.rbegin());
    }
    cout << ans << '\n';

    return 0;
}

