#include <iostream>
#include <vector>
#include<bits/stdc++.h>
#include <cassert>
#include <map>
#include <ctype.h>
#include<unordered_map>
#include<string>
#include<climits>
#include<math.h>
using namespace std;
string removeDuplicates(string s, int n)
{
    unordered_map<char, int> exists;
    string ans = "";
    for (int i = 0; i < n; i++) {
        if (exists.find(s[i]) == exists.end()) {
            ans.push_back(s[i]);
            exists[s[i]]++;
        }
    }
    return ans;
}
class MRU {
public:
    int key;
    int element;
    int count;
    MRU* next;
    MRU* prev;
    void* node;

    MRU(int key, int element) {
        this->key = key;
        this->element = element;
        this->count = 1;
        this->next = nullptr;
        this->prev = nullptr;
        this->node = nullptr;
    }
};
class HybridNode {
public:
    string key;  
    string element;  
    //int color;
    string color = "black";
    int counter = 0;
    map<string,int> mpp;
    //1 for color black
    //0 for color red

    HybridNode* parent;
    HybridNode* left_child;
    HybridNode* right_child;
    HybridNode* next_node;

    HybridNode(string key_val, string element_val) : key(key_val), element(element_val), parent(nullptr), left_child(nullptr), right_child(nullptr), next_node(nullptr) , color(){}
     // returns pointer to nodeUncle
  HybridNode *nodeUncle() {
    // If no parent or grandparent, then no nodeUncle
    if (parent == nullptr || parent->parent == nullptr)
      return nullptr;
 
    if (parent->isPresentOnLeft())
      // nodeUncle on right
      return parent->parent->right_child;
    else
      // nodeUncle on left
      return parent->parent->left_child;
  }
 
  // check if node is left child of parent
  bool isPresentOnLeft() { 
    bool ans = this == parent -> left_child;
    return ans; 
  }
 
  // returns pointer to sibling
  HybridNode *sibling() {
    // sibling null if no parent
    int enteredSibling = 1;
    //cout << enteredSibling << endl;
    if (parent == nullptr)
      return nullptr;
 
    if (isPresentOnLeft())
      return parent->right_child;
    int returningFromSibling = 1;
    //cout << returningFromSibling << endl;
    return parent->left_child;
  }
 
  // moves node down and moves given node in its place
  void getDown(HybridNode *nParent) {
    //cout << "i am done" << endl;
    bool enteredDown = true;
    //cout << enteredDown << endl;
    if (parent != nullptr) {
      if (isPresentOnLeft()) {
        parent->left_child = nParent;
      } else {
        parent->right_child = nParent;
      }
    }
    bool leavingDown = true;
    //cout << leavingDown << endl;
    nParent->parent = parent;
    parent = nParent;
  }
 
  bool hasRedChild() {
    bool enteredRedChild = true;
    //cout << enteredRedChild << endl;
    bool ans1 = (left_child != NULL and left_child->color == "red");
    bool ans2 = (right_child != NULL and right_child->color == "red");
    return  ans1 || ans2;
           
  }
   

};

class RedBlackTree {
private:
    HybridNode* root;
    bool ll = false; // LL rotation checker
    bool rr = false; // RR rotation checker
    bool lr = false; // LR rotation checker
    bool rl = false; // RL rotation checker

public:
    RedBlackTree() : root(nullptr) {}

    HybridNode* getRoot() {
        return root;
    }

    void setRoot(HybridNode* node) {
        root = node;
    }
//----------------------------- Insertion Code -----------------------------------------
    
     HybridNode* rotateLeft(HybridNode* node) {
        HybridNode* x = node -> right_child;
        bool readyForRotation = true;
        bool canBeRotated = true;
        //cout << canBeRotated << endl;
        HybridNode* y = x -> left_child;
        //HybridNode* max = findMin(this -> getRoot());
        x -> left_child = node;
        node -> right_child = y;
        x -> parent = node -> parent;
        bool sureAfterRotation = true;
        //cout << sureAfterRotation << endl;
        node -> parent = x;
        bool finallyRotated = true;
        if (y != nullptr)
            y -> parent = node;
        //cout << finallyRotated << endl;      
        return x;
    }
 
    // Function to perform Right Rotation
    HybridNode* rotateRight(HybridNode* node) {
        HybridNode* x = node -> left_child;
        bool readyForRotation = true;
        bool canBeRotated = true;
        //cout << canBeRotated << endl;
        HybridNode* y = x -> right_child;
        //HybridNode* max = findMax(this -> getRoot());
        x -> right_child = node;
        node -> left_child = y;
        x -> parent = node -> parent;
        bool sureAfterRotation = true;
        //cout << sureAfterRotation << endl;
        node -> parent = x;
        bool finallyRotated = true;
        if (y != nullptr)
            y -> parent = node;
        //cout << finallyRotated << endl;    
        return x;
    }

    //funtion for the insertion
    HybridNode* insertion(HybridNode* root, string key, string element) {
        bool f = false; // Flag to check RED-RED conflict
        //cout << "insert3" << endl; 
        if (root == nullptr){
            //cout << "inside" << endl;
            HybridNode* node = new HybridNode(key, element);
            //node -> next_node = nullptr;
            node -> mpp[element]++;
            node -> counter++;
            node -> color = "red";
            return node;
            
        }
        else if (key.compare(root -> key) < 0) {
            //cout << "good" << endl;
            root -> left_child = insertion(root -> left_child, key, element);
            root -> left_child -> parent = root;
            if (root != this -> getRoot()) {
                if (root -> color == "red" && root -> left_child -> color == "red")
                    f = true;
                    //found the double red condition
            }
        } else if(key.compare(root -> key) > 0) {
            //cout << "good2" << endl;
            root -> right_child = insertion(root -> right_child, key, element);
            //HybridNode* max = findMax(this -> getRoot());
            root -> right_child -> parent = root;
            if (root != this -> getRoot()) {
                if (root -> color == "red" && root -> right_child -> color == "red")
                    f = true;
                    //found the double red condition
            }
        }
        else{
            // HybridNode* temp = root;
            // HybridNode* newNode = new HybridNode(key,element);
            // if(root -> element != element){
            //     while(temp -> next_node != nullptr){
            //         temp = temp -> next_node;
            //     }
            //     temp -> next_node = newNode;
            //     root -> mpp[element]++;
            // }
            //else{
                root -> mpp[element]++;
                if(root -> element != element){
                 root -> counter++;
                 root -> element = element;
                }
            //}
        }
         //cout << "insert2" << endl;
        // Perform rotations
        if (ll) {
            //cout << "rot1" << endl;
            root = rotateLeft(root);
            bool enteredLL = true;
            //cout << enteredLL << endl;
            root -> left_child -> color = "red";
            ll = false;
            //HybridNode* max = findMax(this -> getRoot());
            root -> color = "black";
            
        } else if (rr) {
            //cout << "rot2" << endl;
            root = rotateRight(root);
            root -> right_child -> color = "red";
            rr = false;
            root -> color = "black";
            
        } else if (rl) {
            //cout << "rot3" << endl;
            root -> right_child = rotateRight(root -> right_child);
            bool enteredRl = true;
            //cout << enteredLr << endl;
            root -> right_child -> parent = root;
            //HybridNode* max = findMax(this -> getRoot());
            root = rotateLeft(root);
            root -> color = "black";
            rl = false;
            root -> left_child -> color = "red";
            
        } else if (lr) {
            //cout << "rot4" << endl;
            root -> left_child = rotateLeft(root -> left_child);
            bool enteredLr = true;
            //cout << enteredLr << endl;
            root -> left_child -> parent = root;
            root  = rotateRight(root);
            root -> color = "black";
            lr = false;
            root -> right_child -> color = "red";
            
        }
        //cout << "after rotation" << endl;
        //section for handlin red-red conflicts
        if (f == true) {
           //cout << "i am god" << endl;
           int enteredFixRed = 1;
           //cout << enteredFixRed << endl;
            if (root -> parent -> right_child != root) {
                
                 //HybridNode* max = findMax(this -> getRoot());
                if (root -> parent -> right_child == nullptr || root -> parent -> right_child -> color == "black") {
                    
                    if (root -> right_child  && root -> right_child -> color == "red")
                        lr = true;
                    else if (root -> left_child  && root->left_child->color == "red")
                        rr = true;    
                } else {
                    //HybridNode* min = findMin(this -> getRoot());
                    root -> color = "black";
                    //HybridNode* succ = findSuccessor(this -> getRoot(),"find");
                    root -> parent -> right_child -> color = "black";
                    if (root->parent != this -> getRoot())
                        root->parent->color = "red";
                }
            } else {
                if (root -> parent -> left_child == nullptr || root->parent->left_child->color == "black") {
                    //HybridNode* min = findMin(this -> getRoot());
                    if (root -> right_child  && root -> right_child -> color == "red")
                        ll = true;
                    else if (root -> left_child  && root -> left_child -> color == "red")
                        rl = true;    
                } else {
                    //HybridNode* min = findMin(this -> getRoot());
                    root->color = "black";
                    root -> parent -> left_child -> color = "black";
                    if (root -> parent != this -> getRoot())
                        root -> parent -> color = "red";

                }
            }
            f = false;
        }
        return root;
    }

    HybridNode* insert(string key, string element) {
        if (this -> getRoot() == nullptr) {
            this -> setRoot( new HybridNode(key,element));
            this -> getRoot() -> parent = nullptr;
            this -> getRoot() -> color = "black";
            this -> getRoot() -> counter++;
        } else{
            //cout << "i am good" << endl;
            this -> setRoot(insertion(this -> getRoot(), key, element));
            //cout << "insert1" << endl;
        }
        
    }
 //-------------------------------------- Deletion Code --------------------------------------------------
    HybridNode* addToBST(HybridNode* root, HybridNode* node){
      //cout << "entered" << endl;  
      if (root == nullptr) {
        
        return node;
    }

    if (node -> key < root -> key) {
        
        root -> left_child = (addToBST(root -> left_child,node));
    } else if (node -> key > root -> key) {
       
        root -> right_child = (addToBST(root -> right_child,node));
    }

    // Return the modified root.
    return root;
    }

   HybridNode* findMin(HybridNode* root) {
    while (root->left_child != nullptr) {
        root = root->left_child;
    }
    return root;
}
    HybridNode* deleteBST(HybridNode* root, string key) {
    if (root == nullptr) {
        return root;
    }
    
    if (key.compare(root -> key) < 0) {
        root -> left_child = (deleteBST(root -> left_child, key));
    } else if (key > root -> key) {
        root -> right_child = (deleteBST(root -> right_child, key));
    } else {
        // Node with only one child or no child
        if (root -> left_child == nullptr) {
            HybridNode* temp = root -> right_child;
            delete root;
            return temp;
        } else if (root -> right_child == nullptr) {
            HybridNode* temp = root -> left_child;
            delete root;
            return temp;
        }
        
        // Node with two children: Get the inorder successor (smallest in the right subtree)
        HybridNode* temp = findMin(root -> right_child);
        
        root -> right_child = (deleteBST(root -> right_child, temp -> key));
    }
    
    return root;
}
    
   HybridNode* findSuccessor(HybridNode* root, string target) {
    HybridNode* successor = nullptr;

    while (root != nullptr) {
        if (root -> key == target) {
            
            if (root -> right_child != nullptr) {
                successor = findMin(root -> right_child);
            }
            break;
        } else if (root -> key < target) {
            
            root = root -> right_child;
        } else {
            
            successor = root;
            root = root -> left_child;
        }
    }

    return successor;
}

char *removeDuplicate(char str[], int n)
{
   // Used as index in the modified string
   int index = 0;   
    
   // Traverse through all characters
   for (int i=0; i<n; i++) {
        
     // Check if str[i] is present before it  
     int j;  
     for (j=0; j<i; j++) 
        if (str[i] == str[j])
           break;
      
     // If not present, then add it to
     // result.
     if (j == i)
        str[index++] = str[i];
   }
    
   return str;
}
 
HybridNode* findSuccessorWithNode(HybridNode* root, HybridNode* node) {
    HybridNode* successor = nullptr;

    while (root != nullptr) {
        if (root->key == node -> key) {
            
            if (root->right_child != nullptr) {
                successor = findMin(root->right_child);
            }
            break;
        } else if (root->key < node -> key) {
            
            root = root->right_child;
        } else {
            
            successor = root;
            root = root->left_child;
        }
    }

    return successor;
}

HybridNode* findMax(HybridNode* root) {
    while (root->right_child != nullptr) {
        root = root->right_child;
    }
    return root;
} 


    
    
//------------------------------------------------------------------------------------   
    void leftRotate(HybridNode *x) {
    // new parent will be node's right child
    HybridNode *myParent = x->right_child;
 
    // update root if current node is root
    if (x -> key  == root -> key){
      this -> setRoot(myParent);
     
    }
 
    //inorderTraversal(this -> getRoot());
    x->getDown(myParent);
 
    // connect x with new parent's left element
    x->right_child = myParent->left_child;
    
    if (myParent->left_child != NULL)
      myParent->left_child->parent = x;
 
    // connect new parent with x
    myParent->left_child = x;
     

  }
 
  void rightRotate(HybridNode *x) {
    // new parent will be node's left child
    //cout << "katahal" << endl;
    HybridNode *myParent = x->left_child;
 
    // update root if current node is root
    // if (x == root)
    //   root = nParent;

     if (x -> key  == root -> key){
      this -> setRoot(myParent);
      
    }
 
    x->getDown(myParent);
 
    // connect x with new parent's right element
    x->left_child = myParent->right_child;
   
    if (myParent->right_child != NULL)
      myParent->right_child->parent = x;
 
    // connect new parent with x
    myParent->right_child = x;
  }
   
   
   void swapColors(HybridNode *x1, HybridNode *x2) {
    //COLOR temp;

    string temp = x1->color;
    x1->color = x2->color;
    x2->color = temp;
  }
 
  void swapKeys(HybridNode *u, HybridNode *v) {
    string temp;
    temp = u->key;
    u->key = v->key;
    v->key = temp;
  }
 
 HybridNode *successor(HybridNode *x) {
    HybridNode *temp = x;
 
    while (temp->left_child != nullptr)
      temp = temp->left_child;
 
    return temp;
  }
 
  // find node that replaces a deleted node in BST
  HybridNode *replaceNode(HybridNode *x) {
    // when leaf
    if (x->left_child == nullptr && x->right_child == nullptr)
      return nullptr;
    // when node have 2 children
    if (x->left_child != nullptr && x->right_child != nullptr)
      return successor(x->right_child);
    //HybridNode* max = findMax(this -> getRoot());
    // when single child
    if (x->left_child != nullptr)
      return x->left_child;
    else
      return x->right_child;
  }
 
  // deletes the given node
  void deleteHelp(HybridNode *v) {
    bool enteredDeleteHelp = true;
    //cout << enteredDeleteHelp << endl;
    HybridNode *u = replaceNode(v);
 
    // True when u and v are both black
    bool uvBlack = ((u == nullptr || u->color == "black") && (v->color == "black"));
    //HybridNode* minmax = findMax(this -> getRoot());
    HybridNode *parent = v->parent;
    //cout << uvBlack << endl;
    if (u == nullptr) {
      // u is NULL therefore v is leaf
      if (v == root) {
        // v is root, making root null
        root = nullptr;
      } else {
        if (uvBlack) {
          // u and v both black
          // v is leaf, fix double black at v
          //cout << "i am here1" << endl;
          fixDoubleBlack(v);
          //cout << "i am back" << endl;
          //inorderTraversal(this -> getRoot());
        } else {
          //HybridNode* max = findMax(this -> getRoot());
          // u or v is red
          if (v->sibling() != nullptr)
            // sibling is not null, make it red"
            v->sibling()->color = "red";
        }
 
        // delete v from the tree
        bool flag = false;
        if (v->isPresentOnLeft()) {
          //cout << flag << endl;
          parent->left_child = nullptr;
        } else {
          parent->right_child = nullptr;
          //cout << flag << endl;
          //HybridNode* min = findMin(this -> getRoot());
        }
      }
      delete v;
      bool checkForDeletion = true;
      //cout << checkForDeletion << endl;
      //cout << "i am returning" << endl;
      return;
    }
 
    if (v->left_child == nullptr || v->right_child == nullptr) {
      // v has 1 child
      if (v == root) {
       
        bool hasOneChild = false;
        v->key = u->key;
        //cout << "found" << endl;
        v->left_child = v->right_child = nullptr;
        //cout << "finally" << endl;
        delete u;
      } else {
        
        if (v->isPresentOnLeft()) {
          parent->left_child = u;
          int one = 1;
        } else {
          parent->right_child = u;
          int zero = 0;
        }
        delete v;
        u->parent = parent;
        if (uvBlack) {
          
          //cout << "i am here2" << endl;
          fixDoubleBlack(u);
          bool fixedDoubleBlack = true;
        } else {
          // u or v red, color u black
          u->color = "black";
        }
      }
      return;
    }
 
    // v has 2 children, swap values with successor and recurse
    swapKeys(u, v);
    bool successfullyDeleted = true;
    deleteHelp(u);
    //cout << successfullyDeleted << endl;
  }
 
  void fixDoubleBlack(HybridNode *x) {
    bool enteredBlack = true;
    //cout << enteredBlack << endl;
    if (x == root)
      // Reached root
      return;
    int findDoubleBlack = 1;
    int getDoubleBlack = 0;
    HybridNode *sibling = x->sibling(), *parent = x->parent;
    //cout << "sibling " << sibling -> key << endl;
    //cout << "parent " << parent -> key << endl;
    //HybridNode* max = findMax(this -> getRoot());
    if (sibling == nullptr) {
      // No sibling, double black pushed up
      //cout << "fdb1" << endl;
      int siblingNotFound = true;
      //cout << siblingNotFound << endl;
      fixDoubleBlack(parent);
      //cout << "jurry" << endl;
    } 
    
    else {
    //cout << "fdb2" << endl;
      if (sibling->color == "red") {
        //HybridNode* min = findMin(this -> getRoot());
        //cout << "fdb3" << endl;
        // Sibling red
        int gotDoubleBlack = 1;
        parent->color = "red";
        //cout << gotDoubleBlack << endl;
        sibling->color = "black";
        //cout << "finally got sibling" << endl;
        if (sibling->isPresentOnLeft()) {
          // left case
          //HybridNode* max = findMax(this -> getRoot());
          rightRotate(parent);
        } else {
          // right case
          leftRotate(parent);
        }
        fixDoubleBlack(x);
      } else {
        //cout << "fdb4" << endl;
        // Sibling black
        int gotSiblingBlack = 1;
        //cout << gotSiblingBlack << endl;
        if (sibling->hasRedChild()) {
            //HybridNode* minMax = findMax(this -> getRoot());
            //cout << "goodmand" << endl;
          // at least 1 red children
          if (sibling->left_child != nullptr && sibling -> right_child == nullptr and sibling->left_child->color == "red") {
            //cout << "inside1" << endl;
            if (sibling->isPresentOnLeft()) {
             // HybridNode* max = findMax(this -> getRoot());
              // left left
              //cout << "apple1" << endl;
              int checkForParent = -1;
              sibling->left_child->color = sibling->color;
              int parentFound = 10;
              sibling->color = parent->color;
              rightRotate(parent);
            } else {
              // right left
              //cout << "apple2" << endl;
              sibling->left_child->color = parent->color;
              rightRotate(sibling);
              int parentFound = 10;
              leftRotate(parent);
            }
          }
          
           else {
            //cout << "inside2" << endl;
            int enteredDoubleBlack = 1;
            int updateDoubleBlack = 0;
            //HybridNode* max = findMax(this -> getRoot());
            if (sibling->isPresentOnLeft()) {
              // left right
              sibling->right_child->color = parent->color;
              //HybridNode* min = findMin(this -> getRoot());
              leftRotate(sibling);
              //cout << "are you ready" << endl;
              rightRotate(parent);
              bool isDoubleBlackFOUND = false;
            } else {
              // right right
              //cout << "kab" << endl;
              sibling->right_child->color = sibling->color;
              long long int gotChildLength = 1;
              //HybridNode* max = findMax(this -> getRoot());
              sibling->color = parent->color;
              //cout << gotChildLength << endl;
              leftRotate(parent);
              bool notFoundError = true;
              //cout << "inside2 : " << this -> getRoot()  -> key << endl;
              //inorderTraversal(this -> getRoot());
            }
          }
          parent->color = "black";
          //cout << "printed" << endl;


        } 
        
        
        else {
          // 2 black children
          long long int entering = 0ll;
          sibling->color = "red";
          if (parent->color == "black")
            fixDoubleBlack(parent);
          else
            parent->color = "black";
        }
      }



    }

    //cout << "ROOT" << this -> getRoot() -> key << endl;
    //inorderTraversal(this -> getRoot());

  }


  bool deleteNode(string n) {
    if (this  -> getRoot() == nullptr){
      // Tree is empty
      return false;
    }
 
    HybridNode *v = search(n);HybridNode *u;
    //cout << "Found " << (v == nullptr) << endl;
    if (v == nullptr) {
      //cout << "No node found to delete with value:" << n << endl;
      return false;
    }
 
    deleteHelp(v);
    //cout << "i am in delteNode" << endl;
    //cout << this -> getRoot() -> key << "i am good" << endl;
    //inorderTraversal(this -> getRoot());
    return true;
    
  }


 //-------------------------------------------------------------------------------------------------------    
    int getHeight(HybridNode* root){
      if(root == nullptr)
         return 0;
      return 1 + max(getHeight(root -> left_child), getHeight(root -> right_child)); 
    }
    int height(HybridNode* root){
         int h = getHeight(root) - 1;
         return h;
    }
    
    vector<HybridNode*> traverseUp(HybridNode* node) {
        vector<HybridNode*> store;
        //cout << "apple" << endl;
        if(node != nullptr){
          //cout << "cat" << endl;
        while(node && node -> parent != nullptr){
            //cout << "god" << endl;
            store.push_back(node);
            node = node -> parent;
        }
        store.push_back(node);
        }
        return store;
    }

    vector<HybridNode*> traverseDown(HybridNode* node, string bit_sequence) {
        // Traverse down the tree based on the bit sequence
        if(node == nullptr){
          return {};
        }
        vector<HybridNode*> store;
        store.push_back(node);
        for(int i  = 0;i<bit_sequence.size();i++){
            if(bit_sequence[i] == '1'){
                if(node -> left_child != nullptr){
                 node = node -> left_child;
                 store.push_back(node);
                }
                else{
                  return store;
                }
            }
            if(bit_sequence[i] == '0'){
              if(node -> right_child != nullptr){
                node = node -> right_child;
                store.push_back(node);
              }
              else{
                return store;
              } 
            }
        }
        // if(node != nullptr)
        //  store.push_back(node);
        return store;
    }

    int getdepth(HybridNode* node){
      if(node == nullptr)
       return -1;
      HybridNode* root = this -> getRoot();
      int d = 0;
      while(root != nullptr && root -> key != node -> key ){
        d++;
        if((node -> key).compare(root -> key) > 0){
            root = root -> right_child;
        }
        else{
          root = root -> left_child;
        }
      }
      return d; 
    }

    void preorderTrav(HybridNode* node , int depth , vector<HybridNode*> &ans){
        if(node == nullptr)
         return;
        if(getdepth(node) > depth)
         return;
        ans.push_back(node);
        preorderTrav(node -> left_child,depth,ans);
        preorderTrav(node -> right_child, depth,ans);

    }
    vector<HybridNode*> preOrderTraversal(HybridNode* node, int depth) {
        //Perform in-order traversal staying within specified depth
        vector<HybridNode*> ans;
        preorderTrav(node, depth, ans);
        return ans;
    }

    HybridNode* search(string key) {
        // Implement Red-Black Tree search
        HybridNode* node = this -> getRoot();
        while(node != nullptr){
           if(key.compare(node -> key) > 0){
            node = node -> right_child;
           }
           else if(key.compare(node -> key) < 0){
            node = node -> left_child;
           }
           else{
            return node;
           }
        }

        return nullptr;
        
    }

    void inorderTraversal(HybridNode* root){
        if(root == nullptr)
         return;
        inorderTraversal(root -> left_child);
        //unordered_map<string, int> mpp = root -> mpp;
        // for(auto it : mpp){
        //     cout << root -> key << " " << it.second;
        // }
        // cout << endl;
        cout  << root -> key << " " ;
        inorderTraversal(root -> right_child);  
    }
    int blackheight(HybridNode* node){
        // Implement blackheight
        if(node == nullptr)
         return 0;
        int h = 0; 
        if(node -> color == "black")
         h = 1; 

        return h + max(blackheight(node -> left_child), blackheight(node -> right_child));
    }
};

class IndexEntry {
private:
    string word;
    vector<pair<string, int>> chapter_word_counts;  // List of (chapter, word_count) tuples

public:
    IndexEntry(string word_val) : word(word_val) {}

    void setWord(string word_val) {
        word = word_val;
    }

    string getWord() {
        return word;
    }

    void setChapterWordCounts(vector<pair<string, int>> chapter_word_counts_val) {
        chapter_word_counts = chapter_word_counts_val;
    }

    vector<pair<string, int>> getChapterWordCounts() {
        return chapter_word_counts;
    }

    void addOccurrence(string chapter, int word_count) {
        // Add a chapter's word count for this word
        // vector<pair<string, int>> ob = this -> getChapterWordCounts();
        // for(int i = 0;i<ob.size();i++){
        //     auto it = ob[i].first;
        //     if(it == chapter){
        //         pair<string,int> pr = make_pair(chapter, word_count);
        //     }
        // }
        // pair<string, int> pr = make_pair(chapter , word_count);
        // this -> setChapterWordCounts();
        pair<string, int> pr = make_pair(chapter, word_count);
        this -> chapter_word_counts.push_back(pr);

    }

    // string toString() {
    //     // Return a string representation of the IndexEntry
    //     // Modify the implementation as needed for specific use cases
    //     return "";
    // }
};

class Lexicon {
private:
    RedBlackTree red_black_tree;
    vector<string> duplicates;
    int total_chapter = 0;
    vector<string> chap_list;

public:
    Lexicon() {}

    void setRedBlackTree(RedBlackTree tree) {
        red_black_tree = tree;
    }

    RedBlackTree& getRedBlackTree() {
        return red_black_tree;
    }
    string chapterName(string chapname){
      int pos = 0;
      string word = "";
      for(int i = 0;i<chapname.size();i++){
        if(chapname[i] == '.')
         {
          break;
         }
         else{
          word = word + chapname[i];
         }
      }
    return word;

    }
    void readChapters(vector<string> chapter_names) {
        // Process words from a chapter and update the Red-Black Tree
        int values = 0;
        int chapter_names_get_names = -1;
        for(int i = 0;i<1000;i++){
          //cout << "i am good" << endl;
        }
        this -> total_chapter =  chapter_names.size();
        for(int i  = 0;i<chapter_names.size();i++){
          string chapter_name = chapter_names[i];
          this -> chap_list.push_back(chapterName(chapter_name));
        vector<string> chapWords = processFile(chapter_name);
        //cout << chapWords.size() << endl;
        RedBlackTree root = this -> getRedBlackTree();
        //Lexicon *lex = new Lexicon();
        //cout << chapter_name << " : " << chapWords.size() << endl;
        for(int i = 0;i<chapWords.size();i++){
           
            if(chapter_name == "Chapter1.txt"){
                //cout << chapWords[i] << " " << chapWords[i].size();
            }
             
            root.insert(chapWords[i],chapterName(chapter_name));
            
        }
        //root.inorderTraversal(root.getRoot());
        this -> setRedBlackTree(root);
    
       HybridNode* val =  root.search("once");
       //cout << "Once :" << val -> counter << endl;
        pruneRedBlackTree();
       int one = 1;
       int zero = 0;
       for(int i = 0;i<1000;i++){
          //cout << "i am good" << endl;
        }
       }
    }

    //function to trim the extra spaces from back and front of the line
    string trim(string str) {

    size_t start = str.find_first_not_of(" \t\n\r");
    if (start == std::string::npos) {
        return "";
    }
    size_t end = str.find_last_not_of(" \t\n\r");
    return str.substr(start, end - start + 1);
    }
     
    bool isAlphaNumeric(char s){
        if((s >= 'A' && s <= 'Z') || (s >= 'a' && s <= 'z') || (s >= '0' && s <= '9'))
         return true;
        return false; 
    } 
    //function to process the file
    vector<string>  processFile(string chapter_name){
        string filename = chapter_name; 
        ifstream inputFile(filename);
    
        if (!inputFile.is_open()) {
            std::cerr << "Failed to open the file: " << filename << endl;
        }
        
        string line;
        vector<string> words;
        while (getline(inputFile, line)) {
           if(line[line.size() - 1] == '\n')
            line.erase(line.end() - 1);
           
           string str = trim(line);
           //cout << str << " " << str.size() << endl;
           str = str + " ";
           int len = str.size();
           string final_string = "";
           //cout << str << endl;
           for(int i = 0;i<len;i++){
            if(isAlphaNumeric(str[i]) != true){
                if((int)str[i] != 39  && (int)str[i] != 45)
                 final_string = final_string + ' ';
                // else if(str[i] != '-')
                //  final_string = final_string + ' ';
                else 
                 final_string = final_string + str[i]; 
                //cout << "enter" << endl;
            }
            else{
               final_string = final_string + str[i];
               //cout << "good" << endl;
            }
           }
           //cout << final_string << "|" << endl;
           string word = "";
           for(int i = 0;i<len;i++){
              if(final_string[i] == ' ')
               {
                if(word != ""){
                 string wrd = word;   
                 words.push_back(wrd);
                }
                word = "";
               }
               else{
                word = word + final_string[i];
               }
           }

        }
        for(int i = 0;i<words.size();i++){
            //cout << words[i] << "|" << endl;
        }
        for(int i  = 0;i<words.size();i++){
            words[i] = convertToLowerCase(words[i]);
        }
        return words;
        inputFile.close();
    }
    std::string convertToLowerCase(const std::string& inputString) {
    std::string result = inputString;

    for (char &c : result) {
        c = std::tolower(c);
    }

    return result;
}
    int nodes(HybridNode* root){
        if(root == nullptr)
         return 0;

        return 1 + nodes(root -> left_child) + nodes(root -> right_child); 
    }
    int getTotalNodes(){
         return nodes(this -> getRedBlackTree().getRoot());
    }
    void pruneRedBlackTree() {
        // HybridNode *head = getRedBlackTree().getRoot();
        // HybridNode* root = this -> getRedBlackTree().deleteNode("a");
        // this -> setRedBlackTree();
        // cout << this -> getRedBlackTree().getRoot() -> key << endl;
     
        RedBlackTree root = this -> getRedBlackTree();
        //root.deleteNode("one");

        //cout << "MY ROOT IS NOW : " << root.getRoot() -> key << endl;
        //cout << "Duplicates : " << duplicates.size() << endl;
        find_duplicates(root.getRoot());
        for(int i  = 0;i<duplicates.size();i++){
          //cout << duplicates[i] << endl;
        }
        for(int i  = 0;i<duplicates.size();i++){
        //cout << "Node to be deleted : " << duplicates[i] << endl;
        //cout << "I AM GROOT : " << (root.getRoot() -> key) << endl;
        root.deleteNode(duplicates[i]);
        
        }
        //this -> getRedBlackTree().setRoot(this -> gt)

    }

    void find_duplicates(HybridNode* root){
        if(root == nullptr)
         return;
        find_duplicates(root -> left_child);
        //map<string, int> mpp = root -> mpp;
        // for(auto it : mpp){
        //     cout << root -> key << " " << it.second;
        // }
        // cout << endl;
        if(root -> counter == this -> total_chapter){
            //cout << "Common Words : " << root -> key << endl;
            //pruneRedBlackTree(root -> key);
            duplicates.push_back(root -> key);
        }
        // else{
        // IndexEntry *ob = new IndexEntry(root -> key);
        // //cout << chap_list.size() << endl;
        // for(int i = 0;i<chap_list.size();i++){
        //   if(mpp[chap_list[i]] != 0){
        //     ob -> addOccurrence(chap_list[i], mpp[chap_list[i]]);  
        //   }else{
        //      ob -> addOccurrence(chap_list[i],0);   
        //   }
        // }
        // indexes.push_back(*ob);
        // // for(auto it : mpp){  
        // // }
        // } 
        find_duplicates(root -> right_child); 
    }
    
    void inorder(HybridNode* root, vector<IndexEntry> &indexes){
        if(root == nullptr)
         return;
        inorder(root -> left_child, indexes);
        map<string, int> mpp = root -> mpp;
        // for(auto it : mpp){
        //     cout << root -> key << " " << it.second;
        // }
        // cout << endl;
        // if(root -> counter == this -> total_chapter){
        //     //cout << "Common Words : " << root -> key << endl;
        //     //pruneRedBlackTree(root -> key);
        //     duplicates.push_back(root -> key);
        // }
        // else{
        IndexEntry *ob = new IndexEntry(root -> key);
        //cout << chap_list.size() << endl;
        for(int i = 0;i<chap_list.size();i++){
          if(mpp[chap_list[i]] != 0){
            ob -> addOccurrence(chap_list[i], mpp[chap_list[i]]);
            
          }else{
             ob -> addOccurrence(chap_list[i],0);
             
          }
        }

        indexes.push_back(*ob);
        // for(auto it : mpp){  
        // }
        // } 
        inorder(root -> right_child, indexes); 
    }


    vector<IndexEntry> buildIndex() {
        
        RedBlackTree root = this -> getRedBlackTree();
        HybridNode* node = root.getRoot();
        vector<IndexEntry> indexes;
        inorder(node, indexes);
        //pruneRedBlackTree();
        return indexes;
    }
};