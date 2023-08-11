#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5, sq = sqrt(maxn) + 1;
int n, q, a[maxn], SQ;
int last;
int mxsz = 0;
struct Block
{
    vector<int> cnt;
    vector<int> li;
    Block() {
        cnt = vector<int>(n+1,0);
        li = {};
    }
} blocks[sq];

void refresh() {
    mxsz = 0;
    int curr = 0;
    vector<int> arr;
    for (int i = 0; i <= last; i++) {
        for (int j: blocks[i].li) arr.push_back(j);
    }
    for (int i = 0; i <= last; i++) {
        blocks[i].cnt = vector<int>(n+1,0);
        blocks[i].li.clear();    
    }
    for (int i: arr) {
        if (blocks[curr].li.size() > SQ) curr++;
        blocks[curr].li.push_back(i);
        blocks[curr].cnt[i]++;
        mxsz = max(mxsz,(int)blocks[curr].li.size());
    }
}

pair<int,vector<int>::iterator> traverse(int x) {
    //returns {block #, iterator}
    int curr = 0;
    for (int i = 0; i <= last; i++) {
        if (curr + blocks[i].li.size() >= x) {
            for (auto it = blocks[i].li.begin(); it != blocks[i].li.end(); ++it) {
                curr++;
                if (curr == x) return {i,it};
            }
        }
        else curr += blocks[i].li.size();
    }
}

void update(int l, int r) {
    //insert l'th element, remove from r'th element
    if (l == r) return; //do nothing
    auto left = traverse(l);
    auto right = traverse(r);
    int val = *right.second;
    blocks[right.first].li.erase(right.second);
    blocks[right.first].cnt[val]--;
    blocks[left.first].li.insert(left.second,val);
    blocks[left.first].cnt[val]++;
    mxsz = max(mxsz,(int)blocks[left.first].li.size());
}


int query(int l, int r, int k) {
    auto left = traverse(l);
    auto right = traverse(r);
    int res = 0;
    if (left.first == right.first) {
        for (auto it = left.second; it != next(right.second); ++it)
            if (*it == k) res++;
        return res;
    }
    for (auto it = left.second; it != blocks[left.first].li.end(); ++it)
        if (*it == k) res++;
    for (auto it = right.second; ; --it) {
        if (*it == k) res++;
        if (it == blocks[right.first].li.begin()) break;
    }
    for (int i = left.first + 1; i < right.first; i++) {
        res += blocks[i].cnt[k];
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    SQ = (int)(sqrt(n));
    for (int i = 0; i < sq; i++) blocks[i].cnt = vector<int>(n+1,0);
    int curr = 0;
    for (int i = 1; i <= n; i++) {
        if (blocks[curr].li.size() > SQ) curr++;
        blocks[curr].li.push_back(a[i]);
        blocks[curr].cnt[a[i]]++;
    }
    last = curr;
    cin >> q;
    int lastans = 0;
    while (q--) {
        if (mxsz > 25 * SQ) refresh();
        int t; cin >> t;
        int l, r; cin >> l >> r;
        l = ((l + lastans - 1) % n) + 1;
        r = ((r + lastans - 1) % n) + 1;
        if (l > r) swap(l,r);
        if (t == 1) {
            update(l,r);
        }
        else {
            int k; cin >> k;
            k = ((k + lastans - 1) % n) + 1;
            lastans = query(l,r,k);
            cout << lastans << endl;
        }
    }
    return 0;
}
