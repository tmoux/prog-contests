#include <bits/stdc++.h>
using namespace std;
using ll = long long;

map<pair<char,char>,char> AND = 
{
    {{'x','x'},'x'},
    {{'x','X'},'0'},
    {{'x','1'},'x'},
    {{'x','0'},'0'},
    {{'X','X'},'X'},
    {{'X','1'},'X'},
    {{'X','0'},'0'},
    {{'1','1'},'1'},
    {{'1','0'},'0'},
    {{'0','0'},'0'},
};

map<pair<char,char>,char> XOR = 
{
    {{'x','x'},'0'},
    {{'x','X'},'1'},
    {{'x','1'},'X'},
    {{'x','0'},'x'},
    {{'X','X'},'0'},
    {{'X','1'},'x'},
    {{'X','0'},'X'},
    {{'1','1'},'0'},
    {{'1','0'},'1'},
    {{'0','0'},'0'},
};

map<pair<char,char>,char> OR = 
{
    {{'x','x'},'x'},
    {{'x','X'},'1'},
    {{'x','1'},'1'},
    {{'x','0'},'x'},
    {{'X','X'},'X'},
    {{'X','1'},'1'},
    {{'X','0'},'X'},
    {{'1','1'},'1'},
    {{'1','0'},'1'},
    {{'0','0'},'0'},
};

char OP(char op, char a, char b) {
    pair<char,char> ab = {a,b};
    pair<char,char> ba = {b,a};
    if (op == '&') {
        if (AND.count(ab)) return AND[ab];
        else return AND[ba];
    }
    else if (op == '|') {
        if (OR.count(ab)) return OR[ab];
        else return OR[ba];  
    }
    else {
        assert(op == '^');
        if (XOR.count(ab)) return XOR[ab];
        else return XOR[ba];
    }
}

struct Tree
{
    char op;
    Tree *left, *right;
    char val;
    Tree(char c) {
        left = right = NULL;
        val = c;
        op = 'x';
    }
    Tree(char o, Tree *l, Tree *r) {
        left = l;
        right = r;
        op = o;
    }

    void resolve() {
        if (left == NULL) {
            return;
        }
        else {
            left->resolve();
            right->resolve();
            val = OP(op,left->val,right->val);    
            //printf("%c%c%c=%c\n",left->val,op,right->val,val);    
        }
    }

    void cleanup() {
        if (left) left->cleanup();
        if (right) cleanup();
        delete this;
    }

    void pr() {
        if (left == NULL) {
            cout << val << '\n';
        }
        else {
            left->pr();
            cout << op << '\n';
            right->pr();
        }
    }
};

Tree* setup(const string& s, int l, int r) {
    //cout << l << ' ' << r << endl;
    if (l == r) {
        return new Tree(s[l]);    
    }
    int depth = 0;
    char op = 'x';
    int idx = -1;
    for (int i = l; i <= r; i++) {
        //cout << "OK " << i << ' ' << s[i] << ' ' << depth << endl;
        if (s[i] == '(') depth++;
        else if (s[i] == ')') depth--;
        else if ((s[i] == '&' || s[i] == '^' || s[i] == '|') && depth == 1) {
            op = s[i];
            idx = i;
            break;
        }
    }
    //cout << "idx found = " << idx << endl;
    assert(idx != -1);
    Tree *left = setup(s,l+1,idx-1);
    Tree *right = setup(s,idx+1,r-1);
    return new Tree(op,left,right);
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    for (int qq = 1; qq <= t; qq++) {
        cout << "Case #" << qq << ": ";
        string s; cin >> s;
        Tree *t = setup(s,0,s.size()-1);
        if (t->left == NULL) {
            if (t->val == '1' || t->val == '0') {
                cout << 0 << '\n';
            }
            else {
                cout << 1 << '\n';
            }
        }
        else {
            t->left->resolve();    
            t->right->resolve();    
            char op = t->op;
            char a = t->left->val;
            char b = t->right->val;
            if (OP(op,a,b) == '1' || OP(op,a,b) == '0') {
                cout << 0 << '\n';
            }
            else {
                //char op character to smth else
                cout << 1 << '\n';
            }
        }
    }
}
