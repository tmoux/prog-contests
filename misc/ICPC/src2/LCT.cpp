/*
LCT is short for link-cut tree.
It is a powerful data structure that supports dynamic trees and sometimes dynamic graphs.
(it supports adding an edge to a forest or removing an edge from a forest)
LCT is based on splay tree, so you will find many similarities between these two data structures.
*/

#include <cstdio>
#include <cstdlib>
#include <algorithm>
 
using namespace std;
 
typedef unsigned int uint;
const int maxn = 110000; //maximum number of vertices in the tree
const uint modi = 51061;
 
struct rec
{
    int ls, rs, p; //ls = left son; rs = right son; p = parent
    uint siz; //siz = size of the subtree
    uint key, sum; //sum: sum of weights in the subtree
    uint mult, add; //two lazy tags
    bool rev; //denote whether this segment has been reverted
};
rec splay[maxn];

void clear(){
    splay[0].p = splay[0].ls = splay[0].rs = splay[0].rev = splay[0].key = splay[0].sum = 0;
    splay[0].siz = 0;
}
 
void update(int x){
    clear();
    splay[x].sum = splay[splay[x].ls].sum + splay[splay[x].rs].sum + splay[x].key;
    splay[x].sum %= modi;
    splay[x].siz = splay[splay[x].ls].siz + splay[splay[x].rs].siz + 1;
    splay[x].siz %= modi;
}
 
void zig(int x){
    int y = splay[x].p, z = splay[y].p;
    if (y == splay[z].ls) splay[z].ls = x;
    else if (y == splay[z].rs) splay[z].rs = x;
    splay[x].p = z;
    if (splay[x].rs) splay[splay[x].rs].p = y;
    splay[y].ls = splay[x].rs;
    splay[x].rs = y;
    splay[y].p = x;
    update(y);
}
 
void zag(int x){
    int y = splay[x].p, z = splay[y].p;
    if (y == splay[z].ls) splay[z].ls = x;
    else if (y == splay[z].rs) splay[z].rs = x;
    splay[x].p = z;
    if (splay[x].ls) splay[splay[x].ls].p = y;
    splay[y].rs = splay[x].ls;
    splay[x].ls = y;
    splay[y].p = x;
    update(y);
}
 
bool is_root(int x){
    return x != splay[splay[x].p].ls && x != splay[splay[x].p].rs;
}

void rev(int x){
    if (!x)return;
    swap(splay[x].ls, splay[x].rs);
    splay[x].rev ^= true;
}
 
void pushdown(int x){
    if (splay[x].rev){
        rev(splay[x].ls);
        rev(splay[x].rs);
        splay[x].rev = false;
    }
    //Todo: Push lazy tags here.
}
void set_root(int x){
    static int q[maxn];
    static int top;
    int i;
    for (i = x; !is_root(i); i = splay[i].p){
        q[++top] = i;
    }
    q[++top] = i;
    while (top){
        pushdown(q[top--]);
    }
    while (!is_root(x)){
        int y = splay[x].p;
        if (is_root(y)){
            if (x == splay[y].ls) zig(x); else zag(x);
        }
        else{
            int z = splay[y].p;
            if (y == splay[z].ls){
                if (x == splay[y].ls) zig(y), zig(x);
                else zag(x), zig(x);
            }
            else{
                if (x == splay[y].rs) zag(y), zag(x);
                else zig(x), zag(x);
            }
        }
    }
    update(x);
}

//this is a special operation on LCT 
void access(int x)
{
    for (int t = 0; x; t = x, x = splay[x].p){
        set_root(x);
        splay[x].rs = t;
        update(x);
    }
}

//we will make x be the new root of the tree it belongs to
void makeroot(int x){
    access(x);
    set_root(x);
    rev(x);
}
 
void split(int x, int y){
    makeroot(x);
    access(y);
    set_root(y);
}
 
//link vertex x and vertex y
void link(int x, int y){
    makeroot(x);
    makeroot(y);
    splay[x].p = y;
}
 
//cut the edge between x and y
void cut(int x, int y){
    split(x, y);
    splay[y].ls = splay[x].p = 0;
    update(y);
}

//Adding edge between u and v: link(u, v);
//Removing edge between u and v: link(u1, v1);
//Adding vertices on route between u and v by c :
/* split(u, v);
   calc(v, 1, c);*/
//Query the sum on route from u to v: split(u1,v1) print(splay[v1].sum);
