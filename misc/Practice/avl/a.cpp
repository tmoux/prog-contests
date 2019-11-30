#include <bits/stdc++.h>
using namespace std;
using ll = long long;

namespace AVL
{
    struct Node
    {
        Node *left, *right;
        int key, height;
    };

    int height(Node *node) {
        return !node ? 0 : node->height;
    }

    void update_height(Node *node) {
        if (node) node->height = max(height(node->left),height(node->right)) + 1;
    }

    int balance(Node *node) {
        return !node ? 0 : height(node->left) - height(node->right);
    }

    Node* new_node(int key) {
        Node *node = new Node();
        node->key = key;
        node->left = node->right = NULL;
        node->height = 1;
        return node;
    }

    Node* rotate_right(Node *y) {
        Node *x = y->left;
        Node *T2 = x->right;
        x->right = y;
        y->left = T2;
        //update heights
        update_height(x);
        update_height(y);
        return x;
    }

    Node *rotate_left(Node *x) {
        Node *y = x->right;
        Node *T2 = y->left;
        y->left = x;
        x->right = T2;
        update_height(x);
        update_height(y);
        //update heights;
    }

    Node *insert(Node *node, int key) {
        if (node == NULL) return new_node(key);
        if (key < node->key)
            node->left = insert(node->left, key);
        else if (key > node->key) 
            node->right = insert(node->right,key);
        else //no duplicates allowed
            return node;
        
        update_height(node);
        int b = balance(node);
        if (b > 1 && key < node->left->key) {
            return rotate_right(node);
        }
        if (b < -1 && key > node->right->key) {
            return rotate_left(node);
        }
        if (b > 1 && key > node->left->key) {
            node->left = rotate_left(node->left);
            return rotate_right(node);
        }
        if (b < -1 && key < node->right->key) {
            node->right = rotate_right(node->right);
            return rotate_left(node);
        }
        return node;
    }

    void preorder(Node *root) {
        if (root != NULL) {
            preorder(root->left);
            cout << root->key << ' ';
            preorder(root->right);
        }
    }

    bool count(Node *node, int key) {
        if (node == NULL) return false;
        if (key < node->key) 
            return count(node->left,key);
        else if (key > node->key)
            return count(node->right,key);
        else return true;
    }

    Node* min_val(Node *node) {
        return node->left?min_val(node->left):node;
    }

    Node* delete_node(Node *root, int key) {
        if (root == NULL) return root;
        if (key < root->key)
            root->left = delete_node(root->left,key);
        else if (key > root->key)
            root->right = delete_node(root->right,key);
        else {
            if ((root->left==NULL)||(root->right==NULL)) {
                Node *temp = root->left ? root->left : root->right;
                if (temp == NULL) {
                    temp = root;
                    root = NULL;
                }
                else {
                    *root = *temp;
                }
                delete temp;
            }
            else {
                Node *temp = min_val(root->right);
                root->key = temp->key;
                root->right = delete_node(root->right,temp->key);
            }
        }

        if (root == NULL) return root;
        update_height(root);
        int b = balance(root);
        if (b > 1 && balance(root->left) >= 0)
            return rotate_right(root);
        if (b > 1 && balance(root->left) < 0) {
            root->left = rotate_left(root->left);
            return rotate_right(root);
        }
        if (b < -1 && balance(root->right) <= 0)
            return rotate_left(root);
        if (b < -1 && balance(root->right) > 0) {
            root->right = rotate_right(root->right);
            return rotate_left(root);
        }
        return root;
    }
};
using namespace AVL;

int main() {
    Node *root = NULL;
    root = insert(root,10);
    root = insert(root,20);
    root = insert(root,30);
    root = insert(root,40);
    root = insert(root,50);
    root = insert(root,25);
    preorder(root);
    cout << '\n';
    cout << count(root,30) << '\n';
    delete_node(root,30);
    cout << count(root,30) << '\n';
    preorder(root);
    cout << '\n';
}
