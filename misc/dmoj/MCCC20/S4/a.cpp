#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define all(x) begin(x),end(x)

struct Node {
	int s, e, m;
	//covers s,e;
	int maxi;
	Node *l, *r;
	
	Node(int a, int b) {
		s = a;
		e = b;
		maxi = 0;
		if (s != e) {
			m = (s+e)/2;
			l = new Node(s,m);
			r = new Node(m+1,e);
		}
		else {
			l = NULL;
			r = NULL;
		}
	}

	void add(int i, int x) {
		if (s == e) {
			maxi = x;
			return;
		}
		if (i <= m) {
			l->add(i,x);
		}
		else if (i > m) {
			r->add(i,x);
		}
		else assert(false);
		maxi = max(l->maxi,r->maxi);
	}

	int getmaxi(int st, int en) {
		if (st <= s && e <= en) {
			return maxi;
		}
		int ret = 0;
		if (st <= m) {
			ret = max(ret,l->getmaxi(st,en));
		}
		if (en > m) {
			ret = max(ret,r->getmaxi(st,en));
		}
		return ret;
	}	
};

const int maxn = 1e5+5;
int N, Q, B;
int a[maxn];
//SQRT
int blk;
int bucket[maxn];
struct Block
{
    int l, r;
    vector<ll> pref;
    vector<pair<int,int>> jump; //(# jumps, # left)

    void refresh() {
        pref.clear();
        jump.clear();
        for (int i = l; i <= r; i++) {
            ll add = pref.empty() ? 0 : pref.back();
            add += a[i];
            pref.push_back(add);
        }
        jump.resize(r-l+1);
        /*
        for (int i = 0; i < jump.size(); i++) {
            int ans = 1;
            int curr = B;
            int L = i+l;
            while (L <= r) {
                if (a[L] <= curr) {
                    curr -= a[L];
                }
                else {
                    curr = B-a[L];
                    ans++;
                }
                L++;
            }
            jump[i] = {ans,curr};
        }
        */
        int pt = r-l+1;
        for (int i = jump.size()-1; i >= 0; i--) {
            while (pt-1 >= 0 && (i==0?0:pref[i-1]) + B < pref[pt-1]) {
                pt--;
            }
            if (pt == r-l+1) {
                int used = pref.back() - (i==0?0:pref[i-1]);
                jump[i] = {1,B-used}; //snd can be 0
            }
            else {
                jump[i] = {jump[pt].first+1,jump[pt].second};
            }
        }
    }
} blocks[maxn];

int GET(int l, int r) {
    int curr = B;
    int ans = 1;
    while (l != 1 && bucket[l] == bucket[l-1] && l <= r) {
        if (a[l] <= curr) {
            curr -= a[l];
        }
        else {
            curr = B-a[l];
            ans++;
        }
        l++;
        //printf("%d: ans = %d, curr = %d\n",l,ans,curr);
    }
    while (l <= r && bucket[l] < bucket[r]) {
        int b = bucket[l];        
        vector<ll>& pref = blocks[b].pref;
        auto it = upper_bound(all(pref),curr);
        if (it == blocks[b].pref.end()) {
            //it's bigger than the whole block
            //assert(curr >= pref.back());
            //cout << "sz = " << pref.size() << endl;
            curr -= pref.back();
        }
        else {
            int idx = distance(pref.begin(),it);
            assert(idx < pref.size());
            ans += blocks[b].jump[idx].first;
            curr = blocks[b].jump[idx].second;
        }
        l += blk;
    }
    while (l <= r) {
        //printf("%d: ans = %d, curr = %d\n",l,ans,curr);
        if (a[l] <= curr) {
            curr -= a[l];
        }
        else {
            curr = B-a[l];
            ans++;
        }
        l++;
    }
    return ans;
}

int brute(int l, int r) {
    int ans = 1;
    int curr = B;
    while (l <= r) {
        if (a[l] <= curr) {
            curr -= a[l];
        }
        else {
            curr = B-a[l];
            ans++;
        }
        l++;
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> Q >> B;
    for (int i = 1; i <= N; i++) {
        cin >> a[i];
    }
    //blk = 1000;
    blk = (int)sqrt(N)+1;
    //sqrt stuff
    for (int i = 1; i <= N; i++) {
        bucket[i] = (i-1)/blk;
        int b = bucket[i];
        blocks[b].r = i;
        if (i == 1 || bucket[i] != bucket[i-1]) {
            blocks[b].l = i;
        }
    }
    //cout << "blk = " << blk << endl;
    for (int b = 0; b <= bucket[N]; b++) {
        blocks[b].refresh();
        /*
        printf("[%d,%d]\n",blocks[b].l,blocks[b].r); 
        for (int i: blocks[b].pref) {
            cout << i << ' ';
        }
        cout << '\n';
        for (auto p: blocks[b].jump) {
            printf("(%d,%d) ",p.first,p.second);
        }
        cout << '\n';
        */
    }
    Node *root = new Node(1,N);
    for (int i = 1; i <= N; i++) {
        root->add(i,a[i]);
    }
    while (Q--) {
        char c; cin >> c;
        if (c == 'Q') {
            int l, r; cin >> l >> r;
            if (root->getmaxi(l,r) > B) {
                cout << -1 << '\n';
            }
            else {
                int ans = GET(l,r);
                //cout << "q " << l << ' ' << r << endl;
                /*
                if (ans != brute(l,r)) {
                    cout << "ans = " << ans << '\n';
                    cout << "brute = " << brute(l,r) << '\n';
                    cout << endl;
                }
                assert(ans == brute(l,r));
                */
                cout << ans << '\n';
            }
        }
        else if (c == 'U') {
            int x, v; cin >> x >> v;
            root->add(x,v);
            a[x] = v;
            blocks[bucket[x]].refresh();
        }
    }
}

