#include <iostream>

class RedBlackTree {
private:
    struct Node {
        int data;
        bool color; // true for BLACK, false for RED
        Node* parent;
        Node* left;
        Node* right;

        Node(int data, bool color, Node* parent = nullptr, Node* left = nullptr, Node* right = nullptr)
            : data(data), color(color), parent(parent), left(left), right(right) {}
    };

    Node* root;
    Node* TNULL;

    void fixDelete(Node* x) {
        while (x != root && x->color) {
            if (x == x->parent->left) {
                Node* w = x->parent->right;
                if (!w->color) {
                    w->color = true;
                    x->parent->color = false;
                    leftRotate(x->parent);
                    w = x->parent->right;
                }
                if (w->left->color && w->right->color) {
                    w->color = false;
                    x = x->parent;
                } else {
                    if (w->right->color) {
                        w->left->color = true;
                        w->color = false;
                        rightRotate(w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = true;
                    w->right->color = true;
                    leftRotate(x->parent);
                    x = root;
                }
            } else {
                Node* w = x->parent->left;
                if (!w->color) {
                    w->color = true;
                    x->parent->color = false;
                    rightRotate(x->parent);
                    w = x->parent->left;
                }
                if (w->right->color && w->right->color) {
                    w->color = false;
                    x = x->parent;
                } else {
                    if (w->left->color) {
                        w->right->color = true;
                        w->color = false;
                        leftRotate(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = true;
                    w->left->color = true;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = true;
    }

    void leftRotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        if (y->left != TNULL) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void rightRotate(Node* x) {
        Node* y = x->left;
        x->left = y->right;
        if (y->right != TNULL) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            root = y;
        } else if (x == x->parent->right) {
            x->parent->right = y;
        } else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    // void rbTransplant(Node* u, Node* v) {
    //     if (u->parent == nullptr) {
    //         root = v;
    //     } else if (u == u->parent->left) {
    //         u->parent->left = v;
    //     } else {
    //         u->parent->right = v;
    //     }
    //     v->parent = u->parent;
    // }

    Node* minimum(Node* node) {
        while (node->left != TNULL) {
            node = node->left;
        }
        return node;
    }

    void deleteNodeHelper(Node* node, int key) {
        Node* z = TNULL;
        Node* x, * y;
        while (node != TNULL) {
            if (node->data == key) {
                z = node;
            }

            if (node->data <= key) {
                node = node->right;
            } else {
                node = node->left;
            }
        }

        if (z == TNULL) {
            std::cout << "Key not found in the tree" << std::endl;
            return;
        }

        y = z;
        bool yOriginalColor = y->color;
        if (z->left == TNULL) {
            x = z->right;
            rbTransplant(z, z->right);
        } else if (z->right == TNULL) {
            x = z->left;
            rbTransplant(z, z->left);
        } else {
            y = minimum(z->right);
            yOriginalColor = y->color;
            x = y->right;
            if (y->parent == z) {
                x->parent = y;
            } else {
                rbTransplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            rbTransplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        if (yOriginalColor) {
            fixDelete(x);
        }
    }

    void fixInsert(Node* k) {
        while (k != root && !k->parent->color) {
            if (k->parent == k->parent->parent->left) {
                Node* u = k->parent->parent->right;
                if (!u->color) {
                    u->color = true;
                    k->parent->color = true;
                    k->parent->parent->color = false;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->right) {
                        k = k->parent;
                        leftRotate(k);
                    }
                    k->parent->color = true;
                    k->parent->parent->color = false;
                    rightRotate(k->parent->parent);
                }
            } else {
                Node* u = k->parent->parent->left;
                if (!u->color) {
                    u->color = true;
                    k->parent->color = true;
                    k->parent->parent->color = false;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->left) {
                        k = k->parent;
                        rightRotate(k);
                    }
                    k->parent->color = true;
                    k->parent->parent->color = false;
                    leftRotate(k->parent->parent);
                }
            }
            if (k == root) {
                break;
            }
        }
        root->color = true;
    }

    // void leftRotate(Node* x) {
    //     Node* y = x->right;
    //     x->right = y->left;
    //     if (y->left != TNULL) {
    //         y->left->parent = x;
    //     }
    //     y->parent = x->parent;
    //     if (x->parent == nullptr) {
    //         root = y;
    //     } else if (x == x->parent->left) {
    //         x->parent->left = y;
    //     } else {
    //         x->parent->right = y;
    //     }
    //     y->left = x;
    //     x->parent = y;
    // }

    // void rightRotate(Node* x) {
    //     Node* y = x->left;
    //     x->left = y->right;
    //     if (y->right != TNULL) {
    //         y->right->parent = x;
    //     }
    //     y->parent = x->parent;
    //     if (x->parent == nullptr) {
    //         root = y;
    //     } else if (x == x->parent->right) {
    //         x->parent->right = y;
    //     } else {
    //         x->parent->left = y;
    //     }
    //     y->right = x;
    //     x->parent = y;
    // }

    // Node* minimum(Node* node) {
    //     while (node->left != TNULL) {
    //         node = node->left;
    //     }
    //     return node;
    // }

    void rbTransplant(Node* u, Node* v) {
        if (u->parent == nullptr) {
            root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }

    Node* search(Node* node, int key) {
        if (node == TNULL || node->data == key) {
            return node;
        }
        if (node->data < key) {
            return search(node->right, key);
        }
        return search(node->left, key);
    }

    Node* find(int key) {
        return search(root, key);
    }

    void inorderHelper(Node* node) {
        if (node != TNULL) {
            inorderHelper(node->left);
            std::cout << node->data << " ";
            inorderHelper(node->right);
        }
    }
   public:
    void inorder() {
        inorderHelper(root);
        std::cout << std::endl;
    }

public:
    RedBlackTree() {
        TNULL = new Node(0, true); // Initialize with BLACK
        TNULL->left = nullptr;
        TNULL->right = nullptr;
        root = TNULL;
    }

    void insert(int key) {
        Node* newNode = new Node(key, false); // New nodes are initially RED
        Node* y = nullptr;
        Node* x = root;

        while (x != TNULL) {
            y = x;
            if (key < x->data) {
                x = x->left;
            } else {
                x = x->right;
            }
        }

        newNode->parent = y;
        if (y == nullptr) {
            root = newNode;
        } else if (key < y->data) {
            y->left = newNode;
        } else {
            y->right = newNode;
        }

        if (newNode->parent == nullptr) {
            newNode->color = true; // If the new node is the root, make it BLACK
            return;
        }

        if (newNode->parent->parent == nullptr) {
            return;
        }

        fixInsert(newNode);
    }

    void deleteNode(int key) {
        deleteNodeHelper(root, key);
    }

    
};

int main() {
    RedBlackTree rbTree;

    // Insertion example
    rbTree.insert(10);
    rbTree.insert(20);
    rbTree.insert(30);
    rbTree.insert(40);
    rbTree.insert(50);
    rbTree.insert(60);

    std::cout << "Inorder traversal after insertion:" << std::endl;
    rbTree.inorder();

    // Deletion example
    rbTree.deleteNode(20);

    std::cout << "Inorder traversal after deletion:" << std::endl;
    rbTree.inorder();

    return 0;
}
