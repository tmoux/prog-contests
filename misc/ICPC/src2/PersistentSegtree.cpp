//Define the node of a persistent segment tree
struct node{
    int l,r,sum;
};
//the persistent segment tree. Warning: Check memory limit before using persistent segment tree!
node tree[maxn*32];
//Storing the root of versions of segment tree
int head[maxn];
//allocate next position. You can implement in a way that support garbage collection.
int nextPos(){
    static int ct;return ++ct;
}

//Building the first version of our segmetn tree
void build(int cur,int l,int r){
  tree[cur].sum = 0;
  tree[cur].l = nextPos();
  tree[cur].r = nextPos();
  if (l == r){
    tree[cur].l = tree[cur].r = 0;
  }
  else{
    int mid = (l+r)>>1;
    build(tree[cur].l,l,mid);
    build(tree[cur].r,mid+1,r);
  }
}

//This function is: currently we are at node cur, which is a node in the latest version of segment tree
//we want to make modifications based on some past segment tree, and the corresponding node in the last version is at last
//we want to add 1 at position key
void modify(int cur,int last,int key,int l,int r){
  //this is creating the node for our latest version
  tree[cur].sum = tree[last].sum;
  tree[cur].l = nextPos();
  tree[cur].r = nextPos();
  if (l == r){
    //base case:add on current version of our segment tree
    tree[cur].sum++;
    tree[cur].l = tree[cur].r = 0;
  }
  else{
    int mid = (l+r)>>1;
    if (key <= mid){
      //we are going to modify in the left part, so we can reuse the right child
      tree[cur].r = tree[last].r;
      modify(tree[cur].l, tree[last].l, key,l, mid);
      //update information for the current version of segment tree
      tree[cur].sum++;
    }
    else
    {
      tree[cur].l = tree[last].l;
      modify(tree[cur].r, tree[last].r, key,mid+1, r);
      tree[cur].sum++;
    }
  }
}

int query(int cur,int last,int l,int r,int k){
  if (l == r) return l;
  int mid = (l+r) >> 1;
  //notice the subtraction here - we want tgo see the dfiffernce between today's version and old versions.
  int ct = tree[tree[cur].l].sum - tree[tree[last].l].sum ;
  //if there are to many larger than mid, the k-th element should be in the left
  if (ct >= k){
    return query(tree[cur].l,tree[last].l,l,mid,k);
  }
  //otherwise,the k-th element should be in the right
  else{
    return query(tree[cur].r, tree[last].r, mid+1, r, k-ct);
  }
}

//Build segment tree to support queres k-th element in a subinterval
void build(int n){
  for (int i = 0;i <= n;++i){
    head[i] = nextPos();
  }
  build(head[0], 1, n);
  for (int i = 1;i <= n;++i){
    modify(head[i], head[i-1],c[i], 1, n);
  }
}
/*Query the k-th element in [l,r]:
printf("%d\n",a[query(head[r], head[l-1], 1, n, k)].key);*/
