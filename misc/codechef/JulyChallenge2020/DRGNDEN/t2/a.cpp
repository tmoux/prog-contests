#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
const int BLK = 400;
int N, Q;

int h[maxn];
ll a[maxn];
int next_left[maxn], next_right[maxn];
int bucket[maxn];
ll sum_left[maxn], sum_right[maxn];
int jump_left[maxn], jump_right[maxn];
int st[maxn], en[maxn];

void UPD(int i, ll x) {
    /*
    int b = bucket[i];
    ll delta = x-a[i];
    a[i] = x;

    sum_right[i] += delta;
    int cur = i;
    for (int j = i; j >= 1 && bucket[j] == b; j--) {
        if (next_right[j] == cur) {
            sum_right[j] += delta;
            cur = j;
        }
    }

    sum_left[i] += delta;
    cur = i;
    for (int j = i; j <= N && bucket[j] == b; j++) {
        if (next_left[j] == cur) {
            sum_left[j] += delta;
            cur = j;
        }
    }
    */
    int b = bucket[i];
    a[i] = x;
    for (int i = st[b]; i <= en[b]; i++) {
        sum_left[i] = a[i];
        if (next_left[i] != -1 && bucket[next_left[i]] == bucket[i]) {
            sum_left[i] += sum_left[next_left[i]];
        }
    }
    for (int i = en[b]; i >= st[b]; i--) {
        sum_right[i] = a[i];
        if (next_right[i] != -1 && bucket[next_right[i]] == bucket[i]) {
            sum_right[i] += sum_right[next_right[i]];
        }
    }
}

ll QLEFT(int b, int c) { //b <= c
    ll ans = 0;
    while (c != -1 && c >= b) {
        if (c == b) {
            ans += a[c];
            break;
        }
        if (jump_left[c] != -1 && jump_left[c] >= b) {
            ans += sum_left[c];
            c = jump_left[c];
        }
        else {
            ans += a[c];
            c = next_left[c];
        }
    }
    if (c != b) return -1;
    else return ans;
}

ll QRIGHT(int b, int c) { //c <= b
    ll ans = 0;
    while (c != -1 && c <= b) {
        if (c == b) {
            ans += a[c];
            break;
        }
        if (jump_right[c] != -1 && jump_right[c] <= b) {
            ans += sum_right[c];
            c = jump_right[c];
        }
        else {
            ans += a[c];
            c = next_right[c];
        }
    }
    if (c != b) return -1;
    else return ans;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> Q;
    map<int,vector<int>> mp;
    for (int i = 1; i <= N; i++) {
        cin >> h[i];
        mp[h[i]].push_back(i);
    }
    for (int i = 1; i <= N; i++) {
        cin >> a[i];
    }
    set<int> s;
    for (auto iter = mp.rbegin(); iter != mp.rend(); ++iter) {
        auto v = iter->second;
        for (int i: v) {
            auto it = s.upper_bound(i);
            next_right[i] = it != s.end() ? *it : -1;
            next_left[i] = it != s.begin() ? *prev(it) : -1;
        }
        for (int i: v) {
            s.insert(i);
        }
    }
    /*
    for (int i = 1; i <= N; i++) {
        cout << i << ": " << next_left[i] << ' ' << next_right[i] << endl;
    }
    */
    //SQRT
    for (int i = 1; i <= N; i++) {
        bucket[i] = (i-1)/BLK;
        if (i == 1 || bucket[i] != bucket[i-1]) st[bucket[i]] = i;
        en[bucket[i]] = i;
    }
    for (int i = 1; i <= N; i++) {
        jump_left[i] = next_left[i];
        sum_left[i] = a[i];
        if (next_left[i] != -1 && bucket[next_left[i]] == bucket[i]) {
            jump_left[i] = jump_left[next_left[i]];
            sum_left[i] += sum_left[next_left[i]];
        }
    }
    for (int i = N; i >= 1; i--) {
        jump_right[i] = next_right[i];
        sum_right[i] = a[i];
        if (next_right[i] != -1 && bucket[next_right[i]] == bucket[i]) {
            jump_right[i] = jump_right[next_right[i]];
            sum_right[i] += sum_right[next_right[i]];
        }
    }
    while (Q--) {
        int t, b, c; cin >> t >> b >> c;
        if (t == 1) {
            UPD(b,c);
        }
        else {
            if (b <= c) {
                cout << QLEFT(b,c) << '\n';
            }
            else {
                cout << QRIGHT(b,c) << '\n';
            }
        }
    }
}
