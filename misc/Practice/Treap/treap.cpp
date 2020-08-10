#include <bits/stdc++.h>
using namespace std;
using ll = long long;

random_device device;
mt19937 rng(device());
uniform_int_distribution<int> gen(1,123456789);
struct Treap
{
    Treap *left, *right;    
    int key, priority;
    int size;
    Treap() {}
    Treap(int k, int p) : key(k), priority(p), size(1), left(NULL), right(NULL) {}
};

Treap* new_treap(int k, int p = gen(rng)) {
    return new Treap(k,p);
}

void update_treap(Treap* rt) {
    rt->size = 1;
    if (rt->left) rt->size += rt->left->size;
    if (rt->right) rt->size += rt->right->size;
}

Treap* rotate_right(Treap* rt) {
    assert(rt->left);
    Treap* nt = rt->left;
    Treap* B = nt->right;
    nt->right = rt;
    rt->left = B;
    update_treap(rt);
    update_treap(nt);
    return nt;
}

Treap* rotate_left(Treap* rt) {
    assert(rt->right);
    Treap* nt = rt->right;
    Treap* B = nt->left;
    nt->left = rt;
    rt->right = B;
    update_treap(rt);
    update_treap(nt);
    return nt;
}

Treap* insert(Treap* rt, Treap* add) {
    if (!rt) return add;
    if (add->key <= rt->key) {
        rt->left = insert(rt->left,add);        
        if (rt->left->priority < rt->priority) 
            return rotate_right(rt);
        return rt;
    }
    else {
        rt->right = insert(rt->right,add);
        if (rt->right->priority < rt->priority)
            return rotate_left(rt);
        return rt;
    }
}

Treap* split(Treap* rt, int k) { //all nodes <= k on left, > k on right
    return insert(rt,new_treap(k,0));
}

Treap* meld(Treap* t1, Treap* t2) {
    if (!t1 && !t2) return NULL;
    if (!t1) return t2;
    if (!t2) return t1;
    if (t1->priority < t2->priority) {
        t1->right = meld(t1->right,t2);        
        return t1;
    }
    else {
        t2->left = meld(t1,t2->left);
        return t2;
    }
}

Treap* erase(Treap* rt) {
    return meld(rt->left,rt->right);
}

int mx = 0;
void debug(Treap* rt, int d) {
    mx = max(mx,d);
    //printf("(%d, %d)\n",rt->key,rt->priority);
    if (rt->left) {
        assert(rt->left->key <= rt->key);
        assert(rt->priority <= rt->left->priority);
    }
    if (rt->right) {
        assert(rt->right->key >= rt->key);
        assert(rt->priority <= rt->right->priority);
    }
    if (rt->left) debug(rt->left,d+1);
    if (rt->right) debug(rt->right,d+1);
}

int main() {
    Treap* a = new_treap(1);
    for (int i = 0; i < 10000; i++) {
        a = insert(a,new_treap(gen(rng)));
    }
    for (int i = 0; i < 100; i++) {
        a = split(a,gen(rng));
        debug(a,0);
        a = erase(a);
        debug(a,0);
    }
    cout << mx << endl;
}
