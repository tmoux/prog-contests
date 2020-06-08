#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pi = pair<int,int>;

const int maxn = 3e5+5;
int n, m, h[maxn];

int parent[maxn];
int og_height[maxn];
int Left[maxn], Right[maxn];
int Find(int x) {
    return parent[x] <= 0 ? x : parent[x] = Find(parent[x]);
}

void Union(int x, int y) {
    x = Find(x);
    y = Find(y);
    if (x == y) return;
    cout << "merge " << x << ' ' << y << endl;
    if (parent[x] > parent[y]) {
        swap(x,y);
    }

    if (Find(Right[x]) == y) {
        Right[x] = Find(Right[y]);
    }
    else if (Find(Left[x]) == y) {
        Left[x] = Find(Left[y]);
    }

    parent[x] += parent[y];
    parent[y] = x;
    og_height[x] = max(og_height[x],og_height[y]);
}

int left_dist(int x) {
    return og_height[Left[Find(x)]] - og_height[Find(x)];
}

int right_dist(int x) {
    return og_height[Right[Find(x)]] - og_height[Find(x)];
}

struct PQ 
{
    priority_queue<pi,vector<pi>,greater<pi>> pq;
    int aux = 0;
    pi getmin() {
        pi p = pq.top();
        return {p.first-aux,p.second};
    }
    void insert(pi p) {
        pq.push({p.first+aux,p.second});
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    memset(parent,-1,sizeof parent);
    cin >> n >> m;
    for (int i = 1; i < n; i++) {
        Right[i] = i+1;
    }
    for (int i = 2; i <= n; i++) {
        Left[i] = i-1;
    }
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
        og_height[i] = h[i];
    }
    for (int i = 1; i < n; i++) {
        if (h[i] == h[i+1]) Union(i,i+1);
    }
    PQ pqa, pqb, pqc;
    for (int i = 1; i <= n; i++) {
        bool can_left = Find(Left[i]) != 0 && (Find(Left[Find(Left[i])]) == 0 || left_dist(Find(Left[i])) < 0);
        int dist_left = left_dist(i);
        bool can_right = Find(Right[i]) != 0 && (Find(Right[Find(Right[i])]) == 0 || right_dist(Find(Right[i])) < 0);
        int dist_right = right_dist(i);

        //cout << i << ": " << can_left << ' ' << can_right << endl;
        /*
        if (i == 4) {
            cout << "huh ";
            cout << (Find(Left[i]) != 0 && (left_dist(Find(Left[i])) < 0)) << endl;
            cout << (Find(Left[i]) != 0) << ' ';
            cout << (left_dist(Find(Left[i])) < 0) << '\n';
            //cout << (left_dist(Find(Left[i]))<0) << endl;
        }
        */
        if (can_left && dist_left > 0 && can_right && dist_right > 0) {
            pqc.insert({min(dist_left,dist_right),Find(i)});
            //cout << "inserting " << min(dist_left,dist_right) << ' ' << Find(i) << endl;
        }
        else {  
            if (can_left && dist_left > 0) {
                pqa.insert({dist_left,Find(i)});
            }
            else if (can_right && dist_right > 0) {
                pqb.insert({dist_right,Find(i)});
            }
        }
    }
    for (int i = 0; i < m; i++) {
        char c; cin >> c;
        pqc.aux++;
        if (c == 'A') pqa.aux++;
        else pqb.aux++;
        cout << c << ":\n";
        cout << "sz: " << pqb.pq.size() << endl;
        if (!pqb.pq.empty()) cout << pqb.getmin().first << endl;
        while (!pqc.pq.empty() && pqc.getmin().first == 0) {
            pi p = pqc.getmin(); pqc.pq.pop();
            int x = p.second;
            if (left_dist(x) == right_dist(x)) {
                Union(Left[Find(x)],x);
                Union(x,Right[Find(x)]);
            }
            else if (left_dist(x) < right_dist(x)) {
                Union(Left[Find(x)],x);
                //cout << "adding " << right_dist(x) << endl;
                pqb.insert({right_dist(x),Find(x)});
            }
            else {
                Union(x,Right[Find(x)]);
                pqa.insert({left_dist(x),Find(x)});
            }
        }
        while (!pqa.pq.empty() && pqa.getmin().first == 0) {
            pi p = pqa.getmin(); pqa.pq.pop();
            int x = p.second;
            if (Right[Find(x)] != 0 && left_dist(Right[Find(x)]) > 0) {
                pqa.insert({left_dist(Right[Find(x)]),Right[Find(x)]});
            }
            Union(Left[Find(x)],x);
        }
        while (!pqb.pq.empty() && pqb.getmin().first == 0) {
            pi p = pqb.getmin(); pqb.pq.pop();
            int x = p.second;
            if (Left[Find(x)] != 0 && right_dist(Left[Find(x)]) > 0) {
                pqb.insert({right_dist(Left[Find(x)]),Left[Find(x)]});
            }
            Union(x,Right[Find(x)]);
        }
    }
}

