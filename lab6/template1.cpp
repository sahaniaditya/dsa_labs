#include <iostream>
#include <vector>
#include<bits/stdc++.h>
using namespace std;

class HybridNode {
public:
    string key;  
    string element;  
    int color;
    unordered_map<string,int> mpp;
    //1 for color black
    //0 for color red
    HybridNode* parent;
    HybridNode* left_child;
    HybridNode* right_child;
    HybridNode* next_node;

    HybridNode(string key_val, string element_val) : key(key_val), element(element_val), parent(nullptr), left_child(nullptr), right_child(nullptr), next_node(nullptr) , color(-1){}

    HybridNode *uncle() {
    // If no parent or grandparent, then no uncle
    if (parent == NULL or parent -> parent == NULL)
      return NULL;
 
    if (parent->isOnLeft())
      // uncle on right
      return parent->parent->right_child;
    else
      // uncle on left
      return parent->parent->left_child;
  }
 
  // check if node is left child of parent
  bool isOnLeft() { return this == parent -> left_child; }
 
  // returns pointer to sibling
  HybridNode *sibling() {
    // sibling null if no parent
    if (parent == NULL)
      return NULL;
 
    if (isOnLeft())
      return parent -> right_child;
 
    return parent -> left_child;
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
    return (left_child != NULL and left_child->color == 0) or
           (right_child != NULL and right_child->color == 0);
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
            node -> color = 0;
            return node;
            
        }
        else if (key.compare(root -> key) < 0) {
            //cout << "good" << endl;
            root -> left_child = insertion(root -> left_child, key, element);
            root -> left_child -> parent = root;
            if (root != this -> getRoot()) {
                if (root -> color == 0 && root -> left_child -> color == 0)
                    f = true;
                    //found the double red condition
            }
        } else if(key.compare(root -> key) > 0) {
            //cout << "good2" << endl;
            root -> right_child = insertion(root -> right_child, key, element);
            root -> right_child -> parent = root;
            if (root != this -> getRoot()) {
                if (root -> color == 0 && root -> right_child -> color == 0)
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
            root -> color = 1;
            root -> left_child -> color = 0;
            ll = false;
        } else if (rr) {
            //cout << "rot2" << endl;
            root = rotateRight(root);
            root -> color = 1;
            root -> right_child -> color = 0;
            rr = false;
        } else if (rl) {
            //cout << "rot3" << endl;
            root -> right_child = rotateRight(root -> right_child);
            root -> right_child -> parent = root;
            root = rotateLeft(root);
            root -> color = 1;
            root -> left_child -> color = 0;
            rl = false;
        } else if (lr) {
            //cout << "rot4" << endl;
            root -> left_child = rotateLeft(root -> left_child);
            root -> left_child -> parent = root;
            root  = rotateRight(root);
            root -> color = 1;
            root -> right_child -> color = 0;
            lr = false;
        }
        //cout << "after rotation" << endl;
        //section for handlin red-red conflicts
        if (f) {
            if (root -> parent -> right_child == root) {
                if (root -> parent -> left_child == nullptr || root->parent->left_child->color == 1) {
                    if (root -> left_child  && root -> left_child -> color == 0)
                        rl = true;
                    else if (root -> right_child  && root -> right_child -> color == 0)
                        ll = true;
                } else {
                    root -> parent -> left_child -> color = 1;
                    root->color = 1;
                    if (root -> parent != this -> getRoot())
                        root -> parent -> color = 0;
                }
            } else {
                if (root -> parent -> right_child == nullptr || root -> parent -> right_child -> color == 1) {
                    if (root -> left_child  && root->left_child->color == 0)
                        rr = true;
                    else if (root -> right_child  && root -> right_child -> color == 0)
                        lr = true;
                } else {
                    root -> parent -> right_child -> color = 1;
                    root -> color = 1;
                    if (root->parent != this -> getRoot())
                        root->parent->color = 0;
                }
            }
            f = false;
        }
        return root;
    }

    HybridNode* insert(string key, string element) {
        //cout << key << " InsertThis" << endl;
        if (this -> getRoot() == nullptr) {
            //cout << "insertrootf" << endl;
            this -> setRoot( new HybridNode(key,element));
            this -> getRoot() -> color = 1;
            this -> getRoot() -> parent = nullptr;
        } else{
            //cout << "i am good" << endl;
            this -> setRoot(insertion(this -> getRoot(), key, element));
            //cout << "insert1" << endl;
        }
        //cout << this -> getRoot() -> key << " " << ((this -> getRoot() -> parent) ? this -> getRoot() -> parent -> key : "none") << endl;
        
    }
 //-------------------------------------- Deletion Code --------------------------------------------------
   HybridNode* searchTreeHelper(HybridNode* node, string key) {
		if (node == nullptr || key == node->key) {
			return node;
		}

		if (key < node->key) {
			return searchTreeHelper(node->left_child, key);
		} 
		return searchTreeHelper(node->right_child, key);
	}

	// fix the rb tree modified by the delete operation
	void fixDelete(HybridNode* x) {
        cout << "i am here " << (x == nullptr) << endl;
		HybridNode* s;
        
        if(x == nullptr)
         return;
        cout << (x == nullptr) << endl;
		while ( x != root && x -> color == 1) {
            cout << "click" << endl;
			if (x == x->parent->left_child) {
                cout << "enteredif" << endl;
				s = x->parent->right_child;
				if (s->color == 0) {
					// case 3.0
					s->color = 1;
					x->parent->color = 0;
					leftRotate(x->parent);
					s = x->parent->right_child;
				}

				if (s->left_child->color == 1 && s->right_child->color == 1) {
					// case 3.2
					s->color = 0;
					x = x->parent;
				} else {
					if (s->right_child->color == 1) {
						// case 3.3
						s->left_child->color = 1;
						s->color = 0;
						rightRotate(s);
						s = x->parent->right_child;
					} 

					// case 3.4
					s->color = x->parent->color;
					x->parent->color = 1;
					s->right_child->color = 1;
					leftRotate(x->parent);
					x = root;
				}
			}
            
            
            
            
             else {
                 cout << "enteredelse" << endl;
				s = x->parent->left_child;
				if (s->color == 0) {
					// case 3.0
					s->color = 1;
					x->parent->color = 0;
					rightRotate(x->parent);
					s = x->parent->left_child;
				}

				if (s->right_child->color == 1 && s->right_child->color == 1) {
					// case 3.2
					s->color = 0;
					x = x->parent;
				} else {
					if (s->left_child->color == 1) {
						// case 3.3
						s->right_child->color = 1;
						s->color = 0;
						leftRotate(s);
						s = x->parent->left_child;
					} 

					// case 3.4
					s->color = x->parent->color;
					x->parent->color = 1;
					s->left_child->color = 1;
					rightRotate(x->parent);
					x = root;
				}
			}





		}
        cout << "belowfixf" << endl;
		x->color = 1;



	}


	void rbTransplant(HybridNode* u, HybridNode* v){
        //cout  << "rbIn" << this -> getRoot() -> key  << endl;
        //cout << this -> getRoot() -> parent -> key << endl;
        cout << ((u == nullptr)) << endl;
        cout << ((v == nullptr)) << endl;
		if (u && u->parent == nullptr) {
            cout << "com1" << endl;
			this -> setRoot(v);
            cout << "rbIN123" << this -> getRoot() -> key << endl;
		} else if (u == u->parent->left_child){
            cout << "com2" << endl;
			u->parent->left_child = v;

		} else {
            cout << "com3" << endl;
			u->parent->right_child = v;
		}
        cout << "gulab" << endl;
        cout << ((u == nullptr)||(v == nullptr)) << endl;
        if(v != nullptr)
		 v->parent = u->parent;

        cout << "rbOut" << endl;
	}

	void deleteNodeHelper(HybridNode* node, string key) {
        cout << "deleteHelp" << endl;
		// find the node containing key
		HybridNode* z = nullptr;
		HybridNode* x;HybridNode* y;
		while (node != nullptr){
			if (node->key.compare(key) == 0) {
				z = node;
			}

			if (node->key.compare(key) < 0) {
				node = node->right_child;
			} else {
				node = node->left_child;
			}
		}

		if (z == nullptr) {
			cout<<"Couldn't find key in the tree"<<endl;
			return;
		} 

		y = z;
        cout << "good1" << endl;
		int y_original_color = y->color;
		if (z->left_child == nullptr) {
			x = z->right_child;
            cout << "in1" << endl;
			rbTransplant(z, z->right_child);
            cout << "out1" << endl;
		} else if (z->right_child == nullptr) {
			x = z->left_child;
            cout << "in2" << endl;
			rbTransplant(z, z->left_child);
            cout << "out2" << endl;
		} else {
			y = minimum(z->right_child);
			y_original_color = y->color;
			x = y->right_child;
			if (y->parent == z) {
				x->parent = y;
			} else {
                cout << "in3" << endl;
				rbTransplant(y, y->right_child);
                cout << "out3" << endl;
				y->right_child = z->right_child;
				y->right_child->parent = y;
			}
            cout << "Root : " << this -> getRoot() -> key << endl;
            cout << "in4" << endl;
			rbTransplant(z, y);
            cout << "Root : " << this -> getRoot() -> key << endl;
            cout << "out4" << endl;
			y->left_child = z->left_child;
			y->left_child->parent = y;
			y->color = z->color;
		}
        cout << "last" << endl;
		delete z;
        cout << "rengoku" << endl;
        cout << (this -> root == nullptr) << endl;
        cout << "Root : " << this -> getRoot() -> element << endl;
		if (y_original_color == 1){
			fixDelete(x);
		}
	}
	


    HybridNode* searchTree(string k) {
		return searchTreeHelper(this->root, k);
	}

	// find the node with the minimum key
	HybridNode* minimum(HybridNode* node) {
		while (node->left_child != nullptr) {
			node = node->left_child;
		}
		return node;
	}

	// find the node with the maximum key
	HybridNode* maximum(HybridNode* node) {
		while (node->right_child != nullptr) {
			node = node->right_child;
		}
		return node;
	}

	// find the successor of a given node
	HybridNode* successor(HybridNode* x) {
		// if the right subtree is not null,
		// the successor is the leftmost node in the
		// right subtree
		if (x->right_child != nullptr) {
			return minimum(x->right_child);
		}

		// else it is the lowest ancestor of x whose
		// left child is also an ancestor of x.
		HybridNode* y = x->parent;
		while (y != nullptr && x == y->right_child) {
			x = y;
			y = y->parent;
		}
		return y;
	}

	// find the predecessor of a given node
	HybridNode* predecessor(HybridNode* x) {
		// if the left subtree is not null,
		// the predecessor is the rightmost node in the 
		// left subtree
		if (x->left_child != nullptr) {
			return maximum(x->left_child);
		}

		HybridNode* y = x->parent;
		while (y != nullptr && x == y->left_child) {
			x = y;
			y = y->parent;
		}

		return y;
	}

	// rotate left at node x
	void leftRotate(HybridNode* x) {
        cout << "leftRotate" << endl;
		HybridNode* y = x->right_child;
		x->right_child = y->left_child;
		if (y->left_child != nullptr) {
			y->left_child->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			this->root = y;
		} else if (x == x->parent->left_child) {
			x->parent->left_child = y;
		} else {
			x->parent->right_child = y;
		}
		y->left_child = x;
		x->parent = y;
	}

	// rotate right at node x
	void rightRotate(HybridNode* x) {
        cout << "rightRotate" << endl;
		HybridNode* y = x->left_child;
		x->left_child = y->right_child;
		if (y->right_child != nullptr) {
			y->right_child->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			this->root = y;
		} else if (x == x->parent->right_child) {
			x->parent->right_child = y;
		} else {
			x->parent->left_child = y;
		}
		y->right_child = x;
		x->parent = y;
	}

    // void deleteNode(int data) {
	// 	deleteNodeHelper(this->root, data);
	// }
     bool deleteNode(string key) {
        // Implement Red-Black Tree deletion
        cout << "deleteNode" << endl;
        deleteNodeHelper(this->getRoot(), key);
        return true;
    }


//----------------------------------------------------------------------------------------    
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
        if(node == nullptr)
         return {};
        cout << node -> key << " ";
        preOrderTraversal(node -> left_child,0);
        preOrderTraversal(node -> right_child,0); 
        return {"apple"};

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
        cout << root -> color << " " << root -> key << endl;
        inorderTraversal(root -> right_child);  
    }
    int blackheight(HybridNode* node){
        // Implement blackheight
        if(node == nullptr)
         return 0;
        int h = 0; 
        if(node -> color == 1)
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
        // Prune the Red-Black Tree by deleting common words
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
    ob -> readChapters({"abc.txt","abc1.txt"});
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
    //ob -> getRedBlackTree().preOrderTraversal(ob -> getRedBlackTree().getRoot(),0);
    cout << ob -> getRedBlackTree().getRoot() -> key  << endl;
    cout << "i am here" << endl;
    ob -> getRedBlackTree().deleteNode("b");
    cout << "apple" << endl;
    ob -> getRedBlackTree().inorderTraversal(ob -> getRedBlackTree().getRoot());
    cout << ob -> getRedBlackTree().getRoot() -> key << endl;

   

}
