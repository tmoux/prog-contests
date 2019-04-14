#include <bits/stdc++.h>
using namespace std;

//split elephants into sqrt(N) blocks, where
//cnt(i) is the # of cameras needed to cover the rest of the block,
//and nxt(i) is the next element not covered by using cnt(i) cameras
//These can be precomputed in O(N) time by
//traversing the array backwards.
//When moving an elephant, at most two blocks are changed:
//the one that is was removed from,
//and the one that it is now placed in. Updating a block takes O(sqrt(N)) time.
//We can rebuild the structure O(sqrt(N)) times
//
const int maxn = 150005;
int N, M, L;
int BLOCK;
int pos[maxn];
int bucket[maxn], cnt[maxn], nxt[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> L >> M;
    BLOCK = sqrt(N) + 1;
    for (int i = 1; i <= N; i++) {
        cin >> pos[i];
    }
    //SQRT decomposition
    memset(bucket,-1,sizeof bucket);
    for (int i = 1; i <= N; i++) {
        bucket[i] = (i-1)/BLOCK;
    }
    while (M--) {

    }

    return 0;
}

