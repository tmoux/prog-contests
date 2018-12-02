#include <iostream>
#include <vector>
#include <map>
#include <set>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
int Q;
vector<int> adj[maxn];
int sub_size[maxn];
vector<pair<char,int>> queries;
bool vis[maxn];

struct Node
{
    int id, maxheight;
    bool active;
    pair<pair<Node*,int>,pair<Node*,int>> top2;
    map<int,pair<Node*,int>> alls; //Node* -> (which subtree, depth from centroid) 
    Node* parent;
    Node(int _id) {
        id = _id;    
        maxheight = 0;
        parent = NULL;
        active = false;
        top2.first.first = NULL;
        top2.second.first = NULL;
    }

    void updateTop(Node* child) {
        int dist = child->maxheight + alls[child->id].second;
        if (top2.first.first == child) {
            top2.first = {child,dist};
        }
        else if (top2.second.first == child) {
            top2.second = {child,dist};
        }
        else {
            if (dist > top2.first.second) {
                top2.first = {child,dist};
            }
            else if (dist > top2.second.second) {
                top2.second = {child,dist};
            }
        }
        if (top2.first.first && top2.second.first && top2.second.second > top2.first.second) {
            swap(top2.first,top2.second);
        }
    }

    void propUp(int childid) {
        maxheight = max(maxheight,alls[childid].second);
        updateTop(alls[childid].first);
        if (parent) parent->propUp(childid);
    }

    void update() {
        active = true;
        if (parent) {
            parent->propUp(id);
        }
    }

    int query(int target) {
        if (id == target) {
            return maxheight;
        }
        Node* sub = alls[target].first;
        int height = alls[target].second;
        if (!active) return sub->query(target);

        int deepest = 0;
        if (top2.first.first && top2.first.first != sub) deepest = top2.first.second;
        else if (top2.second.first && top2.second.first != sub) deepest = top2.second.second;
        return max(deepest + height, sub->query(target));
    }
    /*
    void debug() {
        cout << "ID = " << id << '\n';
        cout << "Alls\n";
        for (auto p: alls) {
            printf("%d subtree: %d, depth=%d\n",p.first,p.second.first ? p.second.first->id : 0,p.second.second);
        }
        if (top2.first) {
            printf("Top 1: %d tree with height %d\n",top2.first->id,top2.first->maxheight);
        }
        if (top2.second) {
            printf("Top 2: %d tree with height %d\n",top2.second->id,top2.second->maxheight);
        }
        printf("Maxheight: %d\n",maxheight);
    }
    */
};
Node *nodes[maxn], *treeforid[maxn];

int dfs_size(int i, int par) {
    sub_size[i] = 1;
    for (int j: adj[i]) {
        if (!vis[j] && j != par) {
            sub_size[i] += dfs_size(j,i);
        }
    }
    return sub_size[i];
}

int get_centroid(int i, int par, int compSize) {
    for (int j: adj[i]) {
        if (!vis[j] && j != par) {
            if (sub_size[j] * 2 > compSize) {
                return get_centroid(j,i,compSize);
            }
        }
    }
    return i;
}

void dfs_depth(int i, int par, int dep, Node* ni) {
    ni->alls[i] = {NULL,dep};
    for (int j: adj[i]) {
        if (!vis[j] && j != par) {
            dfs_depth(j,i,dep+1,ni);
        }
    }
}

Node* create_decomp(int i) {
    int compSize = dfs_size(i,i);
    int centroid = get_centroid(i,i,compSize);
    vis[centroid] = true;
    nodes[centroid] = new Node(centroid);
    for (int j: adj[centroid]) {
        if (!vis[j]) {
            dfs_depth(j,centroid,1,nodes[centroid]);
            Node* nj = create_decomp(j);
            nj->parent = nodes[centroid];
            nodes[centroid]->alls[nj->id].first = nj;
            for (auto p: nj->alls) {
                nodes[centroid]->alls[p.first].first = nj;
            }
        }
    }
    return nodes[centroid];
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    //freopen("newbarn.in","r",stdin); 
    //freopen("newbarn.out","w",stdout);
    //get input
    cin >> Q;
    queries.resize(Q);
    int idx = 0;
    for (int i = 0; i < Q; i++) {
        cin >> queries[i].first >> queries[i].second;
        if (queries[i].first == 'B') ++idx;
        if (queries[i].first == 'B' && queries[i].second != -1) {
            int u = idx, v = queries[i].second;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
    }
    //make the centroid-decomposition trees 
    for (int i = 1; i <= idx; i++) {
        if (!vis[i]) {
            create_decomp(i);
        }
    }

    //update treeforid using the roots
    for (int i = 1; i <= idx; i++) {
        if (nodes[i]->parent == NULL) {
            treeforid[i] = nodes[i];
            for (auto& p: nodes[i]->alls) {
                treeforid[p.first] = nodes[i];
            }
        }
    }
    //now we simulate the queries
    idx = 0;
    for (int i = 0; i < Q; i++) {
        pair<char,int> qu = queries[i];
        if (qu.first == 'B') {
            nodes[++idx]->update();
        }
        else {
            int ans = treeforid[qu.second]->query(qu.second);        
            cout << ans << '\n';
        }
    }

    /*
    for (int i = 1; i <= idx; i++) {
        nodes[i]->debug();
    }
    */
    

    return 0;
}

/*
 * Two types of queries:
 * 1. Build x: Know which tree x is in. 
 *      First, find the height of the furthest node(child) from it
 *      Then, go through all the parents and update their furthest height from that subtree.
 *
 * 2. Query x: Know whether x is active.
 *      If it is not active, return the answer of the subtree that contains x.
 *      Else, consider the answer of the subtree that x is in. In addition, consider
 *      the deepest subtree that x is not in. Max the current answer with depth(x) + deepest_height.
 *
 *  So, nodes need to know:
 *      Children
 *      Parent
 *      Height of all children
 *      Height of itself
 *      Sorted order (set) of deepest heights of all subtrees
 *      Whether active
 *      For a given node, which subtree it lies in
*/

	

