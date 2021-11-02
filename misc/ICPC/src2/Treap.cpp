struct node
{
    node *ch[2]; //ch[0] = left child; ch[1] = right child;
    int ct,priority,size,key;
    int lsize(){return(ch[0] == NULL)?0:ch[0]->size;}
    int rsize(){return(ch[1] == NULL)?0:ch[1]->size;}
};
typedef node* tree;
void update(tree & o){//this part depends on the actual info to maintain
    o->size = o->ct; o->size += o->lsize(); o->size += o->rsize();
}
void rotate(tree & o,int dir){ //dir = 0: left rotate
    tree temp = o->ch[dir^1]; o->ch[dir^1] = temp->ch[dir]; temp->ch[dir] = o;
    update(o); update(temp); o = temp;
}
void insert(tree & o,int key){
    if (o == NULL){
        o = new node;
        o->size = o->ct = 1;o->priority = rand();o->ch[0]=o->ch[1]=NULL;o->key=key;
    }
    else if (key == o->key){
        o->ct++;o->size++;
    }
    else{
        int dir = (key<o->key)?0:1;
        insert(o->ch[dir],key);
        if (o->ch[dir]->priority>o->priority) rotate(o,dir^1);
        update(o);
    }
}
void remove(tree & o,int key){
    if (key == o->key){
        if (o->ct > 1){
            o->ct--;o->size--;return;
        }
        else if (o->ch[0]==NULL||o->ch[1]==NULL){
            int d = (o->ch[0]==NULL)?0:1;
            tree temp = o; o = o->ch[d^1]; delete temp;
        }
        else{
            int d =(o->ch[0]->priority > o->ch[1]->priority)?1:0;
            rotate(o,d);remove(o,key);
        }
    }
    else{
        int d = (key<o->key)?0:1;
        remove(o->ch[d],key);
    }
    if (o) update(o);
}
