#include <iostream>
using namespace std;

class Node {
public:
    int key;
    string s;
    Node* left;
    Node* right;
    int height;
};


// function which returns height of the node taken as para
int height(Node* N) {
    if (N == NULL)
        return 0;
    return N->height;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

// New node creation
Node* CreateNode(int key, string str) {
    Node* node = new Node();
    node->key = key;
    node->s = str;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return (node);
}

// Rotate right
Node* RRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left),
        height(y->right)) +1;
    x->height = max(height(x->left),
        height(x->right)) +1;
    return x;
}

// Rotate left
Node* LRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(height(x->left),height(x->right)) + 1;
    y->height = max(height(y->left),height(y->right)) + 1;
    return y;
}

// Get the balance factor of each node
int Bfactor(Node* N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

// Insert a node
Node* insertNode(Node* node, int key , string s) {
    // position of node is found just like bst
    if (node == NULL)
        return (CreateNode(key,s));
    if (key < node->key)
        node->left = insertNode(node->left, key , s);
    else if (key > node->key)
        node->right = insertNode(node->right, key , s);
    else
        return node;

    // Update the balance factor of each node and
    // balance the tree
    node->height = 1 + max(height(node->left),height(node->right));
    int balanceFactor = Bfactor(node);
    if (balanceFactor > 1) {
        if (key < node->left->key) {
            return RRotate(node);
        }
        else if (key > node->left->key) {
            node->left = LRotate(node->left);
            return RRotate(node);
        }
    }
    if (balanceFactor < -1) {
        if (key > node->right->key) {
            return LRotate(node);
        }
        else if (key < node->right->key) {
            node->right = RRotate(node->right);
            return LRotate(node);
        }
    }
    return node;
}

// Node with minimum value
Node* MinNode(Node* node) {
    Node* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

// Delete a node
Node* deleteNode(Node* root, int key) {
    // Find the node and delete it
    if (root == NULL)
        return root;
    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if ((root->left == NULL) ||
            (root->right == NULL)) {
            Node* temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            }
            else
                *root = *temp;
            free(temp);
        }
        else {
            Node* temp = MinNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right,
                temp->key);
        }
    }

    if (root == NULL)
        return root;

    // Update the balance factor of each node and
    // balance the tree
    root->height = 1 + max(height(root->left),
        height(root->right));
    int balanceFactor = Bfactor(root);
    if (balanceFactor > 1) {
        if (Bfactor(root->left) >= 0) {
            return RRotate(root);
        }
        else {
            root->left = LRotate(root->left);
            return RRotate(root);
        }
    }
    if (balanceFactor < -1) {
        if (Bfactor(root->right) <= 0) {
            return LRotate(root);
        }
        else {
            root->right = RRotate(root->right);
            return LRotate(root);
        }
    }
    return root;
}

// inorder traversal but in reverse
void printTree(Node* root) {
    if (root != nullptr) {
        printTree(root->right);
        cout << root->key <<" "<< root->s << endl;
        printTree(root->left);
    }
}

void TreeToText(Node* root, string &x){
    if (root != nullptr) {
        TreeToText(root->right , x);
        //cout << root->key << " " << root->s << endl;
        x += root->s + "\t" + std::to_string(root->key) + "\n";   
        TreeToText(root->left, x);
    }
}