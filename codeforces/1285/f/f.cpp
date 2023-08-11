#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n, a[maxn];
vector<int> divi[maxn];
int mu[maxn];
int cnt[maxn];

void mobius_sieve() {
    mu[1] = 1;
    for (int i = 1; i <= 100000; i++) {
        divi[i].push_back(i);
        for (int j = 2*i; j <= 100000; j += i) {
            mu[j] -= mu[i];
            divi[j].push_back(i);
        }
    }
}

int count_coprime(int x) {
    int res = 0;
    for (int d: divi[x]) {
        res += mu[d]*cnt[d];
    }
    return res;
}

void upd(int x, int y) {
    for (int d: divi[x]) {
        cnt[d] += y;
    }
}

int main() {
    scanf("%d",&n);
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        int ai;
        scanf("%d",&ai);
        a[ai] = 1;
        ans = max(ans,(ll)ai);
    }
    mobius_sieve();

    for (int gc = 1; gc <= 100000; gc++) {
        stack<int> st;
        for (int i = 100000/gc; i >= 1; i--) {
            if (!a[i*gc]) continue;
            while (count_coprime(i) > 0) {
                ans = max(ans,1LL*i*st.top()*gc/__gcd(i,st.top()));
                upd(st.top(),-1);
                st.pop();
            }
            upd(i,1);
            st.push(i);
        }
        while (!st.empty()) {
            upd(st.top(),-1);
            st.pop();
        }
    }
    printf("%lld\n",ans);
}
