struct node{
    node *l,*r;
    //key is the priority
    int key,id;
    //distanct to the leftist child - it is used to maintain the properties of the lefitst tree
    int dist;
    int rdist(){return (r==NULL)?0:r->dist;}
    int ldist(){return (l==NULL)?0:l->dist;}
};
node* merge(node*l,node*r)
{
    if (l == NULL) return r;
    if (r == NULL) return l;
    //we want to make sure the root has the smallest key
    if (l->key > r->key) swap(l,r);
    l->r = merge(l->r,r);
    //maintain the properties of the leftist tree
    if (l->ldist() < l->rdist()) swap(l->l,l->r);
    l->dist = l->rdist()+1;
    return l;
}
