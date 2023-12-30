#include <iostream>
#include <vector>
#include<bits/stdc++.h>
using namespace std;

class HybridNode {
public:
    string key;  
    string element;  
    //int color;
    string color = "";
    unordered_map<string,int> mpp;
    //1 for color black
    //0 for color red
    HybridNode* parent;
    HybridNode* left_child;
    HybridNode* right_child;
    HybridNode* next_node;

    HybridNode(string key_val, string element_val) : key(key_val), element(element_val), parent(nullptr), left_child(nullptr), right_child(nullptr), next_node(nullptr) , color(){}
     // returns pointer to uncle
  HybridNode *uncle() {
    // If no parent or grandparent, then no uncle
    if (parent == NULL or parent->parent == NULL)
      return NULL;
 
    if (parent->isOnLeft())
      // uncle on right
      return parent->parent->right_child;
    else
      // uncle on left
      return parent->parent->left_child;
  }
 
  // check if node is left child of parent
  bool isOnLeft() { return this == parent->left_child; }
 
  // returns pointer to sibling
  HybridNode *sibling() {
    // sibling null if no parent
    if (parent == NULL)
      return NULL;
 
    if (isOnLeft())
      return parent->right_child;
 
    return parent->left_child;
  }
 
  // moves node down and moves given node in its place
  void moveDown(HybridNode *nParent) {
    if (parent != NULL) {
      if (isOnLeft()) {
        parent->left_child = nParent;
      } else {
        parent->right_child = nParent;
      }
    }
    nParent->parent = parent;
    parent = nParent;
  }
 
  bool hasRedChild() {
    return (left_child != NULL and left_child->color == "red") or
           (right_child != NULL and right_child->color == "red");
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
        HybridNode* y = x -> left_child;
        x -> left_child = node;
        node -> right_child = y;
        x -> parent = node -> parent;
        node -> parent = x;
        if (y != nullptr)
            y -> parent = node;
        return x;
    }
 
    // Function to perform Right Rotation
    HybridNode* rotateRight(HybridNode* node) {
        HybridNode* x = node -> left_child;
        HybridNode* y = x -> right_child;
        x -> right_child = node;
        node -> left_child = y;
        x -> parent = node -> parent;
        node -> parent = x;
        if (y != nullptr)
            y -> parent = node;
        return x;
    }

    //funtion for the insertion
    HybridNode* insertion(HybridNode* root, string key, string element) {
        bool f = false; // Flag to check RED-RED conflict
        //cout << "insert3" << endl; 
        if (root == nullptr){
            //cout << "inside" << endl;
            HybridNode* node = new HybridNode(key, element);
            node -> next_node = nullptr;
            node -> mpp[element]++;
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
            root -> right_child -> parent = root;
            if (root != this -> getRoot()) {
                if (root -> color == "red" && root -> right_child -> color == "red")
                    f = true;
                    //found the double red condition
            }
        }
        else{
            HybridNode* temp = root;
            HybridNode* newNode = new HybridNode(key,element);
            if(root -> element != element){
                while(temp -> next_node != nullptr){
                    temp = temp -> next_node;
                }
                temp -> next_node = newNode;
                root -> mpp[element]++;
            }
            else{
                root -> mpp[root -> element]++;
            }
        }
         //cout << "insert2" << endl;
        // Perform rotations
        if (ll) {
            //cout << "rot1" << endl;
            root = rotateLeft(root);
            root -> color = "black";
            root -> left_child -> color = "red";
            ll = false;
        } else if (rr) {
            //cout << "rot2" << endl;
            root = rotateRight(root);
            root -> color = "black";
            root -> right_child -> color = "red";
            rr = false;
        } else if (rl) {
            //cout << "rot3" << endl;
            root -> right_child = rotateRight(root -> right_child);
            root -> right_child -> parent = root;
            root = rotateLeft(root);
            root -> color = "black";
            root -> left_child -> color = "red";
            rl = false;
        } else if (lr) {
            //cout << "rot4" << endl;
            root -> left_child = rotateLeft(root -> left_child);
            root -> left_child -> parent = root;
            root  = rotateRight(root);
            root -> color = "black";
            root -> right_child -> color = "red";
            lr = false;
        }
        //cout << "after rotation" << endl;
        //section for handlin red-red conflicts
        if (f) {
            if (root -> parent -> right_child == root) {
                if (root -> parent -> left_child == nullptr || root->parent->left_child->color == "black") {
                    if (root -> left_child  && root -> left_child -> color == "red")
                        rl = true;
                    else if (root -> right_child  && root -> right_child -> color == "red")
                        ll = true;
                } else {
                    root -> parent -> left_child -> color = "black";
                    root->color = "black";
                    if (root -> parent != this -> getRoot())
                        root -> parent -> color = "red";
                }
            } else {
                if (root -> parent -> right_child == nullptr || root -> parent -> right_child -> color == "black") {
                    if (root -> left_child  && root->left_child->color == "red")
                        rr = true;
                    else if (root -> right_child  && root -> right_child -> color == "red")
                        lr = true;
                } else {
                    root -> parent -> right_child -> color = "black";
                    root -> color = "black";
                    if (root->parent != this -> getRoot())
                        root->parent->color = "red";
                }
            }
            f = false;
        }
        return root;
    }

    HybridNode* insert(string key, string element) {
        if (this -> getRoot() == nullptr) {
            this -> setRoot( new HybridNode(key,element));
            this -> getRoot() -> color = "black";
        } else{
            //cout << "i am good" << endl;
            this -> setRoot(insertion(this -> getRoot(), key, element));
            //cout << "insert1" << endl;
        }
        
    }
 //-------------------------------------- Deletion Code --------------------------------------------------
    void leftRotate(HybridNode *x) {
    // new parent will be node's right child
    HybridNode *nParent = x->right_child;
 
    // update root if current node is root
    if (x -> key  == root -> key){
      this -> setRoot(nParent);
      cout << "good" << endl;
      cout << "leftR root : " << this -> getRoot() -> key << endl;
    }
 
    inorderTraversal(this -> getRoot());
    //x->moveDown(nParent);
 
    // connect x with new parent's left element
    x->right_child = nParent->left_child;
    // connect new parent's left element with node
    // if it is not null
    if (nParent->left_child != NULL)
      nParent->left_child->parent = x;
 
    // connect new parent with x
    nParent->left_child = x;
      cout << "before" << endl;
    inorderTraversal(this -> getRoot());

        cout << "kaddu" << endl;

    



  }
 
  void rightRotate(HybridNode *x) {
    // new parent will be node's left child
    cout << "katahal" << endl;
    HybridNode *nParent = x->left_child;
 
    // update root if current node is root
    if (x == root)
      root = nParent;
 
    x->moveDown(nParent);
 
    // connect x with new parent's right element
    x->left_child = nParent->right_child;
    // connect new parent's right element with node
    // if it is not null
    if (nParent->right_child != NULL)
      nParent->right_child->parent = x;
 
    // connect new parent with x
    nParent->right_child = x;
  }
   
   
   void swapColors(HybridNode *x1, HybridNode *x2) {
    //COLOR temp;

    string temp = x1->color;
    x1->color = x2->color;
    x2->color = temp;
  }
 
  void swapValues(HybridNode *u, HybridNode *v) {
    string temp;
    temp = u->key;
    u->key = v->key;
    v->key = temp;
  }
 
 HybridNode *successor(HybridNode *x) {
    HybridNode *temp = x;
 
    while (temp->left_child != NULL)
      temp = temp->left_child;
 
    return temp;
  }
 
  // find node that replaces a deleted node in BST
  HybridNode *BSTreplace(HybridNode *x) {
    // when node have 2 children
    if (x->left_child != NULL and x->right_child != NULL)
      return successor(x->right_child);
 
    // when leaf
    if (x->left_child == NULL and x->right_child == NULL)
      return NULL;
 
    // when single child
    if (x->left_child != NULL)
      return x->left_child;
    else
      return x->right_child;
  }
 
  // deletes the given node
  void deleteHelp(HybridNode *v) {
    HybridNode *u = BSTreplace(v);
 
    // True when u and v are both black
    bool uvBlack = ((u == NULL or u->color == "black") and (v->color == "black"));
    HybridNode *parent = v->parent;
 
    if (u == NULL) {
      // u is NULL therefore v is leaf
      if (v == root) {
        // v is root, making root null
        root = NULL;
      } else {
        if (uvBlack) {
          // u and v both black
          // v is leaf, fix double black at v
          cout << "i am here1" << endl;
          fixDoubleBlack(v);
          cout << "i am back" << endl;
          inorderTraversal(this -> getRoot());
        } else {
          // u or v is red
          if (v->sibling() != NULL)
            // sibling is not null, make it red"
            v->sibling()->color = "red";
        }
 
        // delete v from the tree
        if (v->isOnLeft()) {
          parent->left_child = NULL;
        } else {
          parent->right_child = NULL;
        }
      }
      delete v;
      cout << "i am returning" << endl;
      return;
    }
 
    if (v->left_child == NULL or v->right_child == NULL) {
      // v has 1 child
      if (v == root) {
        // v is root, assign the value of u to v, and delete u
        v->key = u->key;
        v->left_child = v->right_child = NULL;
        delete u;
      } else {
        // Detach v from tree and move u up
        if (v->isOnLeft()) {
          parent->left_child = u;
        } else {
          parent->right_child = u;
        }
        delete v;
        u->parent = parent;
        if (uvBlack) {
          // u and v both black, fix double black at u
          cout << "i am here2" << endl;
          fixDoubleBlack(u);
        } else {
          // u or v red, color u black
          u->color = "black";
        }
      }
      return;
    }
 
    // v has 2 children, swap values with successor and recurse
    swapValues(u, v);
    deleteHelp(u);
  }
 
  void fixDoubleBlack(HybridNode *x) {
    if (x == root)
      // Reached root
      return;
 
    HybridNode *sibling = x->sibling(), *parent = x->parent;
    cout << "sibling " << sibling -> key << endl;
    cout << "parent " << parent -> key << endl;
    if (sibling == NULL) {
      // No sibling, double black pushed up
      cout << "fdb1" << endl;
      fixDoubleBlack(parent);
    } 
    
    else {
    cout << "fdb2" << endl;
      if (sibling->color == "red") {
        cout << "fdb3" << endl;
        // Sibling red
        parent->color = "red";
        sibling->color = "black";
        if (sibling->isOnLeft()) {
          // left case
          rightRotate(parent);
        } else {
          // right case
          leftRotate(parent);
        }
        fixDoubleBlack(x);
      } else {
        cout << "fdb4" << endl;
        // Sibling black
        if (sibling->hasRedChild()) {
            
            cout << "goodmand" << endl;
          // at least 1 red children
          if (sibling->left_child != NULL && sibling -> right_child == NULL and sibling->left_child->color == "red") {
            cout << "inside1" << endl;
            if (sibling->isOnLeft()) {
              // left left
              cout << "apple1" << endl;
              sibling->left_child->color = sibling->color;
              sibling->color = parent->color;
              rightRotate(parent);
            } else {
              // right left
              cout << "apple2" << endl;
              sibling->left_child->color = parent->color;
              rightRotate(sibling);
              leftRotate(parent);
            }
          }
          
           else {
            cout << "inside2" << endl;
            if (sibling->isOnLeft()) {
              // left right
              sibling->right_child->color = parent->color;
              leftRotate(sibling);
              rightRotate(parent);
            } else {
              // right right
              cout << "kab" << endl;
              sibling->right_child->color = sibling->color;
              sibling->color = parent->color;
              leftRotate(parent);
              cout << "inside2 : " << this -> getRoot()  -> key << endl;
              inorderTraversal(this -> getRoot());
            }
          }
          parent->color = "black";
          cout << "printed" << endl;


        } 
        
        
        else {
          // 2 black children
          sibling->color = "red";
          if (parent->color == "black")
            fixDoubleBlack(parent);
          else
            parent->color = "black";
        }
      }



    }

    cout << "ROOT" << this -> getRoot() -> key << endl;
    inorderTraversal(this -> getRoot());



  }


  HybridNode* deleteNode(string n) {
    if (root == NULL)
      // Tree is empty
      return nullptr;
 
    HybridNode *v = search(n), *u;
 
    if (v->key != n) {
      cout << "No node found to delete with value:" << n << endl;
      return nullptr;
    }
 
    deleteHelp(v);
    cout << "i am in delteNode" << endl;
    cout << this -> getRoot() -> key << "i am good" << endl;
    inorderTraversal(this -> getRoot());
    return (this -> getRoot());
    
  }







 //-------------------------------------------------------------------------------------------------------    
    int height(HybridNode* root){
        if(root == nullptr)
         return 0;
        return 1 + max(height(root -> left_child), height(root -> right_child)); 
    }
    vector<HybridNode*> traverseUp(HybridNode* node) {
        vector<HybridNode*> store;
        if(node != nullptr){
        while(node -> parent != nullptr){
            store.push_back(node);
            node = node -> parent;
        }
        }
    }

    vector<HybridNode*> traverseDown(HybridNode* node, string bit_sequence) {
        // Traverse down the tree based on the bit sequence
        vector<HybridNode*> store;
        for(int i  = 0;i<bit_sequence.size();i++){
            store.push_back(node);
            if(bit_sequence[i] == '1' && node -> left_child){
                node = node -> left_child;
            }
            else if(bit_sequence[i] == '0' && node -> right_child){
                node = node -> right_child;
            }
        }
    }

    vector<string> preOrderTraversal(HybridNode* node, int depth) {
        //Perform in-order traversal staying within specified depth

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
        cout  << root -> key << " " << root -> color << endl;
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

    string toString() {
        // Return a string representation of the IndexEntry
        // Modify the implementation as needed for specific use cases
        return "";
    }
};

class Lexicon {
private:
    RedBlackTree red_black_tree;

public:
    Lexicon() {}

    void setRedBlackTree(RedBlackTree tree) {
        red_black_tree = tree;
    }

    RedBlackTree getRedBlackTree() {
        return red_black_tree;
    }

    void readChapters(vector<string> chapter_names) {
        // Process words from a chapter and update the Red-Black Tree
        for(int i  = 0;i<chapter_names.size();i++){
          string chapter_name = chapter_names[i];
        vector<string> chapWords = processFile(chapter_name);
        //cout << chapWords.size() << endl;
        RedBlackTree root = this -> getRedBlackTree();
        //Lexicon *lex = new Lexicon();
        for(int i = 0;i<chapWords.size();i++){
            root.insert(chapWords[i], chapter_name);
            
        }
        //root.inorderTraversal(root.getRoot());
        this -> setRedBlackTree(root);
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
                if((int)str[i] != 39)
                 final_string = final_string + ' ';
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
        // for(int i = 0;i<words.size();i++){
        //     cout << words[i] << "|" << endl;
        // }
        return words;
        inputFile.close();
    }

    void pruneRedBlackTree() {
        // HybridNode *head = getRedBlackTree().getRoot();
        // HybridNode* root = this -> getRedBlackTree().deleteNode("a");
        // this -> setRedBlackTree();
        // cout << this -> getRedBlackTree().getRoot() -> key << endl;

        RedBlackTree root = this -> getRedBlackTree();
        root.deleteNode("a");
        this -> setRedBlackTree(root);
        //this -> getRedBlackTree().setRoot(this -> gt)

    }
    void inorder(HybridNode* root, vector<IndexEntry> &indexes){
        if(root == nullptr)
         return;
        inorder(root -> left_child, indexes);
        unordered_map<string, int> mpp = root -> mpp;
        // for(auto it : mpp){
        //     cout << root -> key << " " << it.second;
        // }
        // cout << endl;
        IndexEntry *ob = new IndexEntry(root -> key);
        for(auto it : mpp){
            ob -> addOccurrence(it.first, it.second);
        }
        indexes.push_back(*ob);
        inorder(root -> right_child, indexes);  
    }
    vector<IndexEntry> buildIndex() {
        RedBlackTree root = this -> getRedBlackTree();
        HybridNode* node = root.getRoot();
        vector<IndexEntry> indexes;
        inorder(node, indexes);
        return indexes;
    }
};
int main(){
    // RedBlackTree* ob = new RedBlackTree();
    // cout << "i am here1" << endl;
    // ob -> insert("a","apple");
    // ob -> inorderTraversal(ob -> getRoot());
    // cout << "i am here2" << endl;
    // ob -> insert("b","ball");
    // cout << "i am here3" << endl;
    // ob -> insert("c","cat");
    // cout << "i am here" << endl;
    // ob -> insert("d","cat");
    // ob -> insert("e","cat");
    // ob -> insert("f","fish");
    // //ob -> insert("g","good");
    // ob -> inorderTraversal(ob -> getRoot());
    // cout << ob -> height(ob -> getRoot());
    // cout << "-------------" << endl;
    // cout << ob -> getRoot() -> key;
    // cout << ob -> blackheight(ob -> getRoot()) << endl;
    Lexicon *ob = new Lexicon();
    ob -> processFile("abc.txt");
    vector<string> words;
    ob -> readChapters({"abc.txt"});
    //ob -> readChapter("")
    // cout << "good" << endl;
    // cout << (ob -> getRedBlackTree().getRoot() == nullptr);
    // //ob -> getRedBlackTree().inorderTraversal(ob -> getRedBlackTree().getRoot(), );
    // vector<IndexEntry> vec = ob -> buildIndex();
    // cout << endl;
    // for(auto it : vec){
    //    vector<pair<string, int>> v = it.getChapterWordCounts();
    //    cout << it.getWord() << "|";
    //    for(auto ite : v){
    //     cout << ite.first << " " << ite.second << ":";
    //    }
    //    cout << endl;
    // }
    // cout << "apple" << endl;
    ob -> getRedBlackTree().inorderTraversal(ob -> getRedBlackTree().getRoot());
    cout << "root : " << ob -> getRedBlackTree().getRoot() -> key << endl;
    ob -> pruneRedBlackTree();
    cout << "apple" << endl;
    ob -> getRedBlackTree().inorderTraversal(ob -> getRedBlackTree().getRoot());
    cout << "root : " << ob -> getRedBlackTree().getRoot() -> key << endl;

   

}
